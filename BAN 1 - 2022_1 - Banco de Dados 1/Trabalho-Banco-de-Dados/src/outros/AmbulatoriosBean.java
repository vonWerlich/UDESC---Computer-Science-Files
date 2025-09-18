package outros;

public class AmbulatoriosBean {
   private int nroa;
   private int capacidade;
   private int andar;
   
   public AmbulatoriosBean(int nroa, int capacidade, int andar) {
       this.nroa= nroa;
       this.capacidade = capacidade;
       this.andar = andar;
   }

    public int getNroa() {
        return nroa;
    }

    public void setNroa(int nroa) {
        this.nroa = nroa;
    }

    public int getCapacidade() {
        return capacidade;
    }

    public void setCapacidade(int capacidade) {
        this.capacidade = capacidade;
    }

    public int getAndar() {
        return andar;
    }

    public void setAndar(int andar) {
        this.andar = andar;
    }
   
    public String toString(){
        return "Nroa: "+nroa+" capacidade: "+capacidade+" andar: "+andar;
    }
}