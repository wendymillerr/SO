import java.util.Scanner;

public class Servidor{
    public static void main(String[] args) {

   
        Fila fila = new Fila(10); // Tamanho máximo da fila = 10
        Memoria memoria = new Memoria();
        Scanner scanner = new Scanner(System.in);
        
        Produtor produtor = new Produtor(fila, scanner);
        Consumidor consumidor = new Consumidor(fila, memoria);


        Thread produtorThread = new Thread(produtor);
        Thread consumidorThread = new Thread(consumidor);


        produtorThread.start();
        consumidorThread.start();


        try {
            produtorThread.join();
            consumidorThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    
}