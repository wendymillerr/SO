public class Requisicao {
    private String tipo;
    private String recurso;
    private String valor;
    
    public Requisicao(String tipo, String recurso, String valor) {
        this.tipo = tipo;
        this.recurso = recurso;
        this.valor = valor;
    }

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    public String getRecurso() {
        return recurso;
    }

    public void setRecurso(String recurso) {
        this.recurso = recurso;
    }

    public String getValor() {
        return valor;
    }

    public void setValor(String valor) {
        this.valor = valor;
    }
    
    
}
