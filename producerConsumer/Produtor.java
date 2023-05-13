import java.util.Scanner;

public class Produtor implements Runnable {
    private Fila fila;
    private Scanner scanner;
    
    public Produtor(Fila fila, Scanner scanner) {
        this.fila = fila;
        this.scanner = scanner;
    }

    
    @Override
    public void run() {
        while (true) {// loop infinito para ficar lendo as entradas do usuário
            try {
                String linha = scanner.nextLine();// lê uma linha de texto do usuário
                String[] partes = linha.split(" ");// divide a linha em partes usando o espaço como separador
                String tipo = partes[0];// a primeira parte da linha é o tipo de requisição (PUT ou CLOSE)
                String recurso = partes[1];// a segunda parte da linha é o recurso da requisição
                String valor = null;

                if (tipo.equals("PUT")) {

                    valor = partes[2];

                    //caso tenha mais de um valor, uni-los em um só
                    for(int i = 3; i < partes.length; i++){
                        if(partes[i]!=null){
                        valor += " " + partes[i] ;// concatena o valor atual com os valores anteriores, separados por espaço
                            
                    }

                    
                }
            }
                Requisicao req = new Requisicao(tipo, recurso, valor);
                fila.adicionar(req);
                if (tipo.equals("CLOSE")) 
                    break;
                
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
