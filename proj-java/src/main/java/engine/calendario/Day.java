package engine.calendario;


import engine.collections.FixedSizeList;

import java.util.function.Predicate;

/**
 * Classe que define um dia.
 * @param <T> Tipo dos elementos guardados.
 */
class Day<T extends Chronological> {
    /** Lista das horas do dia. */
    private final FixedSizeList<Hour<T>> hours;

    /**
     * Cria um dia.
     */
    Day(){
        this.hours = new FixedSizeList<>(24);
    }

    /**
     * Adiciona um elemento a um dia.
     * @param c Elemento a adicionar.
     */
    void addElem(T c){
        int hour = c.getDate().getHour();
        if(this.hours.get(hour) == null) this.hours.set(hour, new Hour<>());
        this.hours.get(hour).addElem(c);
    }

    /**
     * Itera sobre os elementos de um dia por ordem cronológica.
     * @param predicate Função a aplicar a todos os elementos.
     * @return {@code true} se a iteração deve continuar, {@code false} caso contrário.
     */
    boolean iterateForward(Predicate<T> predicate){
        boolean r = true;
        for(int i = 0; r && i < 24; i++){
            Hour<T> h = this.hours.get(i);
            if(h != null) r = h.iterateForward(predicate);
        }
        return r;
    }

    /**
     * Itera sobre os elementos de um dia por ordem cronológica inversa.
     * @param predicate Função a aplicar a todos os elementos.
     * @return {@code true} se a iteração deve continuar, {@code false} caso contrário.
     */
    boolean iterateBackwards(Predicate<T> predicate){
        boolean r = true;
        for(int i = 23; r && i >= 0 ; i--){
            Hour<T> h = this.hours.get(i);
            if(h != null) r = h.iterateBackwards(predicate);
        }
        return r;
    }

    /**
     * Conta o número de elementos do dia.
     * @return O número de elementos do dia.
     */
    long countElements(){
        long count = 0;
        for(int i = 0; i < 24; i++){
            Hour<T> h = this.hours.get(i);
            if(h != null) count += h.getCount();
        }
        return count;
    }
}
