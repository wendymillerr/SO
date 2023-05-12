import java.util.Scanner;

public class Produtor implements Runnable {
    private Fila fila;
    private Scanner scanner;
    
    public Produtor(Fila fila, Scanner scanner) {
        this.fila = fila;
        this.scanner = scanner;
    }

    //coloque um metodo que retorne o tamanho da fila e faça um for para que valor receba partes até o  tamanho 
    
    @Override
    public void run() {
        while (true) {
            try {
                String linha = scanner.nextLine();
                String[] partes = linha.split(" ");
                String tipo = partes[0];
                System.out.println(tipo);
                String recurso = partes[1];
                System.out.println(recurso);
                String valor = null;
                if (tipo.equals("PUT")) {
                    if(partes[3]!=null){
                        valor = partes[2] + partes[3];
                    }else{
                        valor = partes[2];
                    }
                    
                    System.out.println(valor+ partes[3]);
                }
                Requisicao req = new Requisicao(tipo, recurso, valor);
                fila.adicionar(req);
                if (tipo.equals("CLOSE")) {
                    break;
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
