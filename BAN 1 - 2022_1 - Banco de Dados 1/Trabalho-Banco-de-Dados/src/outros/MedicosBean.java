package outros;

import java.util.HashSet;
import java.util.Iterator;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rebeca
 */
public class MedicosBean {
   private int codm;
   private String nome;
   private int idade;    
   private String especialidade;
   private long cpf;
   private String cidade;
   private int nroa;
   private AmbulatoriosBean ambulatorio;

   public MedicosBean(int codm, String nome, int idade, String especialidade, long cpf, String cidade, int nroa) {
       this.codm=codm;
       this.nome= nome;
       this.idade= idade;
       this.especialidade= especialidade;
       this.cpf = cpf;
       this.cidade = cidade;
       this.nroa = nroa;
   }
    /**
     * @return the codm
     */
    public int getCodm() {
        return codm;
    }

    /**
     * @param codm the codm to set
     */
    public void setCodm(int codm) {
        this.codm = codm;
    }

    /**
     * @return the nome
     */
    public String getNome() {
        return nome;
    }

    /**
     * @param nome the nome to set
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * @return the idade
     */
    public int getIdade() {
        return idade;
    }

    /**
     * @param idade the idade to set
     */
    public void setIdade(int idade) {
        this.idade = idade;
    }

    /**
     * @return the especialidade
     */
    public String getEspecialidade() {
        return especialidade;
    }

    /**
     * @param especialidade the especialidade to set
     */
    public void setEspecialidade(String especialidade) {
        this.especialidade = especialidade;
    }

    /**
     * @return the cpf
     */
    public long getCpf() {
        return cpf;
    }

    /**
     * @param cpf the cpf to set
     */
    public void setCpf(long cpf) {
        this.cpf = cpf;
    }

    /**
     * @return the cidade
     */
    public String getCidade() {
        return cidade;
    }

    /**
     * @param cidade the cidade to set
     */
    public void setCidade(String cidade) {
        this.cidade = cidade;
    }

    /**
     * @return the nroa
     */
    public int getNroa() {
        return nroa;
    }

    /**
     * @param nroa the nroa to set
     */
    public void setNroa(int nroa) {
        this.nroa = nroa;
    }
    
    /**
     * @return the ambulatorio
     */
    public AmbulatoriosBean getAmbulatorio() {
        return ambulatorio;
    }

    /**
     * @param ambulatorios the ambulatorio to set
     */
    public void setAmbulatorio(AmbulatoriosBean ambulatorio) {
        this.ambulatorio = ambulatorio;
    }
    
    
    public String toString(){
        StringBuffer sb = new StringBuffer();
        sb.append("codm: "+codm+" nome: "+nome+" idade: "+idade+
                " especialidade: "+especialidade+" cpf: "+cpf+" cidade: "+cidade+" nroa: "+nroa);
        if(ambulatorio!= null)
            sb.append(" andar: "+ambulatorio.getAndar()+" capacidade: "+ambulatorio.getCapacidade());
        return sb.toString();
    }        
}
