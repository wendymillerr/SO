import java.util.Scanner;

public class Servidor{
    public static void main(String[] args) {
        
        Memoria memoria = new Memoria();
        Scanner scanner = new Scanner(System.in);
        Scanner scannerTam = new Scanner(System.in);
        int tamanho = scannerTam.nextInt();
        Fila fila = new Fila(tamanho); // Tamanho máximo da fila 

        
        Produtor produtor = new Produtor(fila, scanner);
        Consumidor consumidor = new Consumidor(fila, memoria);


        Thread produtorThread = new Thread(produtor);
        Thread consumidorThread = new Thread(consumidor);


        produtorThread.start();
        consumidorThread.start();

        /*O método main espera as threads terminarem sua execução com o método join, 
        que aguarda até que as threads tenham terminado.*/
        try {
            produtorThread.join();
            consumidorThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    
}