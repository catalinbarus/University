"""
This module represents the Consumer.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread, Semaphore
import time

class Consumer(Thread):
    """
    Class that represents a consumer.
    """

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        """
        Constructor.

        :type carts: List
        :param carts: a list of add and remove operations

        :type marketplace: Marketplace
        :param marketplace: a reference to the marketplace

        :type retry_wait_time: Time
        :param retry_wait_time: the number of seconds that a producer must wait
        until the Marketplace becomes available

        :type kwargs:
        :param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self, **kwargs)

        self.carts = carts
        self.marketplace = marketplace
        self.retry_wait_time = retry_wait_time

        # Binary semaphore used for restricting access
        self.consumer_sem = Semaphore(1)

    def halt_consumer(self, halt_period):
        time.sleep(halt_period)

    def run(self):
        # For each cart, process the requested commands
        for cart in self.carts:
            # Get a new cart
            # This operation will be synchronized
            self.consumer_sem.acquire()
            cart_id = self.marketplace.new_cart()
            self.consumer_sem.release()

            # Get through all operations
            for operation in cart:

                # Add/Remove a product to cart till the requested quantity is met
                actual_quantity = int(operation['quantity'])
                for _ in range(actual_quantity):

                    # Obtain operation info (Add or Remove)
                    selected_operation = operation['type']

                    # Obtain item on which operations will be performed
                    requested_item = operation['product']

                    # Repeat process till the operation succeeds
                    while True:

                        if selected_operation == 'add':
                            self.consumer_sem.acquire()
                            add_op = self.marketplace.add_to_cart(cart_id, requested_item)
                            self.consumer_sem.release()

                            # If add operation succeeds, go to next one
                            if add_op:
                                break

                            # If not try again in a few seconds
                            self.halt_consumer(self.retry_wait_time)

                        elif selected_operation == 'remove':
                            self.consumer_sem.acquire()
                            rem_op = self.marketplace.remove_from_cart(cart_id, requested_item)
                            self.consumer_sem.release()

                            # If remove operation succeeds, go to next one
                            if rem_op is None:
                                break

                            # If not try again in a few seconds
                            self.halt_consumer(self.retry_wait_time)

            # Consumer is ready to request the order
            self.marketplace.place_order(cart_id)
