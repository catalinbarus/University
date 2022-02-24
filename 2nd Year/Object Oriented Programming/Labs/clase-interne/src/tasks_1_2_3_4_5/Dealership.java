package tasks_1_2_3_4_5;
import java.util.Calendar;
import java.util.Random;

public class Dealership {

    CarType type1 = CarType.Honda;
    CarType type2 = CarType.Mitsubishi;
    CarType type3 = CarType.Toyota;

    /** Inner class for the brand offer. **/
    private class BrandOffer implements Offer {
        int discount;

        public int getDiscount(Car car) {

            if(car.type == type1) {
               discount = car.price*5/100;
            }
            if(car.type == type2) {
                discount = car.price*10/100;
            }
            if(car.type == type3) {
                discount = car.price*15/100;
            }
            return discount;
        }
    }

    /** Inner class for the dealer offer. **/
    private class DealerOffer implements Offer {
        int year = Calendar.getInstance().get(Calendar.YEAR);

        public int getDiscount(Car car) {
            int oldness = year - car.production_year;

            return oldness*100;
        }
    }

    /** Inner class for special offer. **/
    private class SpecialOffer implements Offer {
        Random rand = new Random();

        public int getDiscount(Car car) {
            int random_discount = rand.nextInt(301);

            return random_discount;
        }
    }

    /** Method that can apply a discount after negotiation. **/
    public void negotiate(Car car, Offer offer) {
        Random random = new Random();
        if(random.nextInt(2) == 1){
            car.price = car.price - offer.getDiscount(car);
            System.out.println("Applying Client discount: " + offer.getDiscount(car));
            System.out.println("Final price after negotiation: " + car.price);
        }


    }

    /** Method that prints all available discounts and
     * applies them accordingly.
     **/
    void getFinalPrice(Car car) {
        Dealership deal = new Dealership();
        Dealership.BrandOffer firstdiscount = deal.new BrandOffer();
        Dealership.DealerOffer seconddiscount = deal.new DealerOffer();
        Dealership.SpecialOffer thirddiscount = deal.new SpecialOffer();

        int brand_discount = firstdiscount.getDiscount(car);
        int dealer_discount = seconddiscount.getDiscount(car);
        int special_discount = thirddiscount.getDiscount(car);
        int final_price = car.price - brand_discount - dealer_discount -
                special_discount;

        System.out.println(car.type);
        System.out.println("Initial price: " + car.price);
        System.out.println("Brand discount: " + brand_discount);
        System.out.println("Dealer discount: " + dealer_discount);
        System.out.println("Special discount: " + special_discount);
        System.out.println("Final price: " + final_price);
        car.price = final_price;
    }

}