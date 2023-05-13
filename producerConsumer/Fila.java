import java.util.LinkedList;
import java.util.Queue;

public class Fila {
    private Queue<Requisicao> fila;
    private int limite;
    
    public Fila(int limite) {
        this.fila = new LinkedList<Requisicao>();
        this.limite = limite;
    }
    /*
     *  Se a fila estiver cheia, método entra em espera até que 
     *  haja espaço na fila para a adição da requisição. 
     */
    public synchronized void adicionar(Requisicao req) throws InterruptedException {
        while (fila.size() == limite) {
            wait();
        }
        fila.add(req);// requisição é adicionada na fila
        notifyAll();
    }
    
    public synchronized Requisicao remover() throws InterruptedException {
        while (fila.isEmpty()) {
            wait();
        }
        Requisicao req = fila.remove();
        notifyAll();
        return req;
    }

    public Queue<Requisicao> getFila() {
        return fila;
    }

    
    public int getLimite() {
        return limite;
    }

    public void setLimite(int limite) {
        this.limite = limite;
    }

    
}
