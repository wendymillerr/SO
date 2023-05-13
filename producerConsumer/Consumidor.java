public class Consumidor implements Runnable {
    private Fila fila;
    private Memoria memoria;
    
    public Consumidor(Fila fila, Memoria memoria) {
        this.fila = fila;
        this.memoria = memoria;
    }
    
    @Override
    public void run() {
        while (true) {// Loop infinito para consumir as requisições da fila
            try {
                Requisicao req = fila.remover();// Remove uma requisição da fila
                String tipo = req.getTipo();// Obtém o tipo de requisição (GET, PUT, CLOSE)
                String recurso = req.getRecurso();// Obtém o recurso da requisição
                String valor = req.getValor();// Obtém o valor da requisição, se houver
                if (tipo.equals("GET")) {
                    String resultado = memoria.get(recurso);
                    System.out.println("GET " + recurso + " -> \"" + resultado +"\"");
                } else if (tipo.equals("PUT")) {
                    System.out.println("PUT " + recurso + " -> \"" + valor +"\"");
                    memoria.put(recurso, valor);
                } else if (tipo.equals("CLOSE")) {
                    break;
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
