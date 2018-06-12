package engine.calendario;


import engine.collections.FixedSizeList;

import java.time.LocalDate;
import java.util.function.Predicate;

/**
 * Classe que define um mês.
 * @param <T> Tipo dos elementos guardados.
 */
@SuppressWarnings("Duplicates")
class Month<T extends Chronological> {
    /** Lista dos dias do mês. */
    private final FixedSizeList<Day<T>> days;

    /**
     * Cria um mês.
     * @param month O número de dias que o mês tem.
     */
    Month(int month){
        this.days = new FixedSizeList<>(nrDays(month));
    }

    /**
     * Retorna o número dias que o mês tem.
     * @param m O mês.
     * @return O número dias que o mês tem.
     */
    private int nrDays(int m){
        if(m == 3 || m == 5 || m == 8 || m == 10) return 30;
        if(m == 1 ) return 29;
        return 31;
    }

    /**
     * Adiciona um elemento a um mês.
     * @param c Elemento a adicionar.
     */
    void addElem(T c){
        int day = c.getDate().getDayOfMonth() - 1;
        if(this.days.get(day) == null) this.days.set(day, new Day<>());
        this.days.get(day).addElem(c);
    }

    /**
     * Itera sobre os elementos de um mês por ordem cronológica.
     * @param from A data de início.
     * @param to A data do fim.
     * @param ip Ponto em que está a iteração.
     * @param predicate Função a aplicar a todos os elementos.
     * @return {@code true} se a iteração deve continuar, {@code false} caso contrário.
     */
    boolean iterateForward(LocalDate from, LocalDate to, IterPoint ip, Predicate<T> predicate){
        int fromD;
        int toD;
        if(ip == IterPoint.IS_BOTH){
            fromD = from.getDayOfMonth() - 1;
            toD = to.getDayOfMonth() - 1;
        }else if(ip == IterPoint.IS_START){
            fromD = from.getDayOfMonth() - 1;
            toD = nrDays(to.getMonthValue()) - 1;
        }else if(ip == IterPoint.IS_END){
            fromD = 0;
            toD = to.getDayOfMonth() - 1;
        }else{
            fromD = 0;
            toD = nrDays(to.getMonthValue()) - 1;
        }
        boolean keepGoing = true;
        for(int i = fromD; keepGoing && i <= toD; i++){
            Day<T> d = this.days.get(i);
            if(d != null) keepGoing = d.iterateForward(predicate);
        }
        return keepGoing;
    }

    /**
     * Itera sobre os elementos de um mês por ordem cronológica inversa.
     * @param from  A data de início.
     * @param to A data do fim.
     * @param ip Ponto em que está a iteração.
     * @param predicate Função a aplicar a todos os elementos.
     * @return {@code true} se a iteração deve continuar, {@code false} caso contrário.
     */
    boolean iterateBackwards(LocalDate from, LocalDate to, IterPoint ip, Predicate<T> predicate){
        int fromD;
        int toD;
        if(ip == IterPoint.IS_BOTH){
            fromD = from.getDayOfMonth() - 1;
            toD = to.getDayOfMonth() - 1;
        }else if(ip == IterPoint.IS_START){
            fromD = from.getDayOfMonth() - 1;
            toD = 0;
        }else if(ip == IterPoint.IS_END){
            fromD = nrDays(to.getMonthValue()) - 1;
            toD = to.getDayOfMonth() - 1;
        }else{
            fromD = nrDays(to.getMonthValue()) - 1;
            toD = 0;
        }
        boolean keepGoing = true;
        for(int i = fromD; keepGoing && i >= toD; i--){
            Day<T> d = this.days.get(i);
            if(d != null) keepGoing = d.iterateBackwards(predicate);
        }
        return keepGoing;
    }

    /**
     * Conta o número de elementos do mês.
     * @param from A data de início.
     * @param to A data do fim.
     * @param ip Ponto em que está a iteração.
     * @return O número de elementos do mês.
     */
    long countElements(LocalDate from, LocalDate to, IterPoint ip){
        int fromD;
        int toD;
        if(ip == IterPoint.IS_BOTH){
            fromD = from.getDayOfMonth() - 1;
            toD = to.getDayOfMonth() - 1;
        }else if(ip == IterPoint.IS_START){
            fromD = from.getDayOfMonth() - 1;
            toD = nrDays(to.getMonthValue()) - 1;
        }else if(ip == IterPoint.IS_END){
            fromD = 0;
            toD = to.getDayOfMonth() - 1;
        }else{
            fromD = 0;
            toD = nrDays(to.getMonthValue()) - 1;
        }
        long count = 0;
        for(int i = fromD; i <= toD; i++){
            Day<T> d = this.days.get(i);
            if(d != null) count += d.countElements();
        }
        return count;
    }
}
