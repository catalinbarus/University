"""
This module represents the Marketplace.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Lock
import threading
import time
import unittest
import logging
from logging.handlers import RotatingFileHandler

# Logging configuration
logging.basicConfig(
        handlers=[RotatingFileHandler('./marketplace.log', maxBytes=100000, backupCount=10)],
        level=logging.INFO,
        format="[%(asctime)s] %(levelname)s %(message)s",
        datefmt='%Y-%m-%dT%H:%M:%S')
logging.Formatter.converter = time.gmtime

class TestMarketplace(unittest.TestCase):
    """
    Class that implements the unit tests for all of the methods in marketplace.py.
    """
    def setUp(self):
        self.marketplace = Marketplace(5)

    def test_register_producer(self):
        """
        Test if a producer has registered successfully in the marketplace.
        """
        self.assertEqual(self.marketplace.register_producer(), self.marketplace.producer_id - 1)

    def test_publish_true(self):
        """
        Test if a product has been published into the producer's queue.
        """
        self.marketplace.register_producer()
        self.assertTrue(self.marketplace.publish(0, "prod1"))

    def test_publish_false(self):
        """
        Test if a product failed to publish into the producer's queue.
        """
        self.marketplace.register_producer()

        self.marketplace.items_per_producer[0] = 6
        self.assertFalse(self.marketplace.publish(0, "prod1"))

    def test_new_cart(self):
        """
        Test if a cart was successfully created.
        """
        self.assertEqual(self.marketplace.new_cart(), self.marketplace.num_carts - 1)

    def test_add_to_cart_true(self):
        """
        Test if a product was successfully added to the cart.
        """
        producer_id = self.marketplace.register_producer()
        self.marketplace.publish(producer_id, "prod1")

        cart_id = self.marketplace.new_cart()

        self.assertTrue(self.marketplace.add_to_cart(cart_id, "prod1"))

    def test_add_to_cart_false(self):
        """
        Test if a product failed to be added to a cart.
        """
        producer_id = self.marketplace.register_producer()
        self.marketplace.publish(producer_id, "prod1")

        cart_id = self.marketplace.new_cart()

        self.assertFalse(self.marketplace.add_to_cart(cart_id, "prod2"))

    def test_remove_from_cart(self):
        """
        Test if a product was removed from the cart.
        """
        producer_id = self.marketplace.register_producer()
        self.marketplace.publish(producer_id, "prod1")

        cart_id = self.marketplace.new_cart()
        self.marketplace.add_to_cart(cart_id, "prod1")

        self.marketplace.remove_from_cart(cart_id, "prod1")
        self.assertEqual(self.marketplace.carts_info[cart_id], [])

    def test_place_order(self):
        """
        Test if the right order was placed.
        """
        producer_id = self.marketplace.register_producer()
        self.marketplace.publish(producer_id, "prod1")

        cart_id = self.marketplace.new_cart()
        self.marketplace.add_to_cart(cart_id, "prod1")
        product_list_test = self.marketplace.place_order(cart_id)
        self.assertEqual(product_list_test, ['prod1'])

class Marketplace:
    """
    Class that represents the Marketplace. It's the central part of the implementation.
    The producers and consumers use its methods concurrently.
    """
    def __init__(self, queue_size_per_producer):
        """
        Constructor

        :type queue_size_per_producer: Int
        :param queue_size_per_producer: the maximum size of a queue associated with each producer
        """
        # Num of items per producer
        self.queue_size_per_producer = queue_size_per_producer

        # List of lists, each list consisting of all the items of one producer
        self.items_per_producer = []

        # List of all available products in the marketplace
        self.available_in_market = []

        # Dictionary which holds which producer made what product
        self.manufacturer = {}

        # Number of carts distributed (also used for the id of the cart)
        self.num_carts = 0

        # Number of producers currently in the marketplace (also used for the ids of producers)
        self.producer_id = 0

        # Dictionary which holds the evidence for all products in a cart
        self.carts_info = {}

        # Lock used for the consumer
        self.consumer_lock_object = Lock()

        # Lock used for the cart
        self.cart_lock_object = Lock()

    def register_producer(self):
        """
        Returns an id for the producer that calls this.
        """

        # Assign a new id for the new producer
        producer_id = self.producer_id
        self.producer_id += 1

        # Give them a list to store their products
        self.items_per_producer.append([])

        logging.info(f'Method "register_producer" - output: producer_id = {producer_id}')
        return producer_id

    def publish(self, producer_id, product):
        """
        Adds the product provided by the producer to the marketplace

        :type producer_id: String
        :param producer_id: producer id

        :type product: Product
        :param product: the Product that will be published in the Marketplace

        :returns True or False. If the caller receives False, it should wait and then try again.
        """
        logging.info(f'Method "publish" - input: producer_id = {producer_id}, product = {product}')

        # Get how many items has the producer made
        current_queue_size = len(self.items_per_producer[producer_id])

        # If that number is still in the approved limit add the product
        if current_queue_size < self.queue_size_per_producer:

            # Add the item to the producer's own list
            self.items_per_producer[producer_id].append(product)

            # Remember who made this product
            self.manufacturer[product] = producer_id

            # Add the product to a general purpose list
            self.available_in_market.append(product)

            logging.info(f'Method "publish" - output: True')
            return True

        # If we get here, the producer reached their item limit
        logging.info(f'Method "publish" - output: False')
        return False

    def new_cart(self):
        """
        Creates a new cart for the consumer

        :returns an int representing the cart_id
        """
        # Assign a new cart, with a new id
        cart_id = self.num_carts
        self.num_carts += 1

        # For the new cart, assign a list of products that will go there
        if cart_id not in self.carts_info.keys():
            self.carts_info[cart_id] = []

        logging.info(f'Method "new_cart" - output: cart_id = {cart_id}')
        return cart_id

    def add_to_cart(self, cart_id, product):
        """
        Adds a product to the given cart. The method returns

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to add to cart

        :returns True or False. If the caller receives False, it should wait and then try again
        """

        logging.info(f'Method "add_to_cart" - input: cart_id = {cart_id}, product = {product}')

        # Check if the desired product is available
        if product not in self.available_in_market:
            logging.info(f'Method "add_to_cart" - output: False')
            return False

        self.cart_lock_object.acquire()

        # Delete the product from the producer's own list
        actual_producer = self.manufacturer[product]

        if product in self.items_per_producer[actual_producer]:
            self.items_per_producer[actual_producer].remove(product)

        # Delete the product from the general purpose list
        if product in self.available_in_market:
            self.available_in_market.remove(product)
        self.cart_lock_object.release()

        # Add the product to this cart
        self.carts_info[cart_id].append(product)

        logging.info(f'Method "add_to_cart" - output: True')
        return True

    def remove_from_cart(self, cart_id, product):
        """
        Removes a product from cart.

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to remove from cart
        """
        logging.info(f'Method "remove_from_cart" - input: cart_id = {cart_id}, product = {product}')
        # Add the product back to the general purpose list
        self.available_in_market.append(product)

        # Add the product back to the producer's own list
        actual_producer = self.manufacturer[product]
        self.items_per_producer[actual_producer].append(product)

        # Delete the product from the cart
        if product in self.carts_info[cart_id]:
            self.carts_info[cart_id].remove(product)

        return

    def place_order(self, cart_id):
        """
        Return a list with all the products in the cart.

        :type cart_id: Int
        :param cart_id: id cart
        """
        logging.info(f'Method "place_order" - input: cart_id = {cart_id}')

        products = []
        # Remove the entry matching the given client id
        for cart_key, cart_value in self.carts_info.items():
            if cart_key == cart_id:
                products = cart_value
                del self.carts_info[cart_key]
                break

        self.consumer_lock_object.acquire()
        # Print the removed list of products
        for product in products:
            print(f'{threading.currentThread().name} bought {product}')
        self.consumer_lock_object.release()

        logging.info(f'Method "place_order" - products = {products}')
        return products
