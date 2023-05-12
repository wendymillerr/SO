import java.util.HashMap;

public class Memoria {
    private HashMap<String, String> recursos;

    public Memoria() {
        recursos = new HashMap<String, String>();
    }

    public synchronized String get(String chave) {
        return recursos.getOrDefault(chave, "");
    }

    public synchronized void put(String chave, String valor) {
        recursos.put(chave, valor);
    }
}
