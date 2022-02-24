package Lab3;

public class TestMain {
    public static void main(String[] args){
        Area area_init = new Area();
        Area area = new Area(area_init.candybag, 6, "Strada Roz ");

        area.getBirthdayCard();

        Lindt lindt1 = new Lindt(3, 5, 6);
        Lindt lindt2 = new Lindt(1, 2, 7);

        System.out.println(lindt1.equals(lindt2));


    }

}
