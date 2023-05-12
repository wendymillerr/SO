public class Consumidor implements Runnable {
    private Fila fila;
    private Memoria memoria;
    
    public Consumidor(Fila fila, Memoria memoria) {
        this.fila = fila;
        this.memoria = memoria;
    }
    
    @Override
    public void run() {
        while (true) {
            try {
                Requisicao req = fila.remover();
                String tipo = req.getTipo();
                String recurso = req.getRecurso();
                String valor = req.getValor();
                if (tipo.equals("GET")) {
                    String resultado = memoria.get(recurso);
                    System.out.println(resultado);
                } else if (tipo.equals("PUT")) {
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
