package third;

/** Clasa ce implementeaza toate metodele aferente operatorilor aritmetici. **/
public class Operation implements Minus, Plus, Mult, Div {

    /** Getter si Setter pentru variabila Number. **/
    public float getNumber() {
        return Number;
    }

    public void setNumber(float number) {
        Number = number;
    }

    private float Number;

    /** Constructor ce initializeaza numarul. **/
    public Operation(float Number) {
        this.Number = Number;
    }

    /** Implementarea operatorului de adunare. **/
    public float minus(float Number) {

        this.Number -= Number;
        return this.Number;
    }

    /** Implementarea operatorului de scadere. **/
    public float plus(float Number) {

        this.Number += Number;
        return this.Number;
    }

    /** Implementarea operatorului de inmultire. **/
    public float mult(float Number) {

        this.Number *= Number;
        return this.Number;
    }

    /** Implementarea operatorului de impartire. **/
    public float div(float Number) {

        if(Number != 0) {
            this.Number /= Number;
        }
        return this.Number;
    }
}
