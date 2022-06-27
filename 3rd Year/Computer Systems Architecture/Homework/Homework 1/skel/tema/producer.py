"""
This module represents the Producer.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread, Semaphore
import time

class Producer(Thread):
    """
    Class that represents a producer.
    """

    def __init__(self, products, marketplace, republish_wait_time, **kwargs):
        """
        Constructor.

        @type products: List()
        @param products: a list of products that the producer will produce

        @type marketplace: Marketplace
        @param marketplace: a reference to the marketplace

        @type republish_wait_time: Time
        @param republish_wait_time: the number of seconds that a producer must
        wait until the marketplace becomes available

        @type kwargs:
        @param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self, **kwargs)

        self.products = products
        self.marketplace = marketplace
        self.republish_wait_time = republish_wait_time

        # Binary semaphore used for restricting access
        self.producer_sem = Semaphore(1)

    def halt_producer(self, halt_period):
        time.sleep(halt_period)

    def run(self):

        # Register a new producer
        # This operation will be synchronized
        self.producer_sem.acquire()
        current_prod_id = self.marketplace.register_producer()
        self.producer_sem.release()

        # Repeat this process
        while True:

            # For each product, make it according to its details
            for product in self.products:

                # Extract details (object name, quantity, wait time)
                product_obj = product[0]
                quantity = product[1]
                wait_time = product[2]
                idx = 0

                # Publish that product till the desired quantity is met
                while idx < int(quantity):

                    # If the post failed, wait a different amount of time than normal
                    if self.marketplace.publish(current_prod_id, product_obj) is False:

                        self.halt_producer(self.republish_wait_time)
                    # Else wait its given wait time
                    else:
                        self.halt_producer(wait_time)
                        idx += 1
