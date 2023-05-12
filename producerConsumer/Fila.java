import java.util.LinkedList;
import java.util.Queue;

public class Fila {
    private Queue<Requisicao> fila;
    private int limite;
    
    public Fila(int limite) {
        this.fila = new LinkedList<Requisicao>();
        this.limite = limite;
    }
    
    public synchronized void adicionar(Requisicao req) throws InterruptedException {
        while (fila.size() == limite) {
            wait();
        }
        fila.add(req);
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
}
