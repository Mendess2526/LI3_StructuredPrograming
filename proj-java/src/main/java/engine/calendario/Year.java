package engine.calendario;


import engine.collections.FixedSizeList;

import java.time.LocalDate;
import java.util.function.Predicate;

/**
 * Classe que define um ano.
 * @param <T> Tipo dos elementos guardados.
 */
@SuppressWarnings({"BooleanMethodIsAlwaysInverted", "Duplicates"})
class Year<T extends Chronological> {
    /** Lista dos meses do ano. */
    private final FixedSizeList<Month<T>> months;

    /**
     * Cria um ano.
     */
    Year(){
        this.months = new FixedSizeList<>(12);
    }

    /**
     * Adiciona um elemento a um ano.
     * @param c Elemento a adicionar.
     */
    void addElem(T c){
        int month = c.getDate().getMonthValue() - 1;
        if(this.months.get(month) == null) this.months.set(month, new Month<>(month));
        this.months.get(month).addElem(c);
    }

    /**
     * Itera sobre os elementos de um ano por ordem cronológica.
     * @param from A data de início.
     * @param to A data do fim.
     * @param ip Ponto em que está a iteração.
     * @param predicate Função a aplicar a todos os elementos.
     * @return {@code true} se a iteração deve continuar, {@code false} caso contrário.
     */
    boolean iterateForward(LocalDate from, LocalDate to, IterPoint ip, Predicate<T> predicate){
        int fromM;
        int toM;
        if(ip == IterPoint.IS_BOTH){
            fromM = from.getMonthValue() - 1;
            toM = to.getMonthValue() - 1;
        }else if(ip == IterPoint.IS_START){
            fromM = from.getMonthValue() - 1;
            toM = 11;
        }else if(ip == IterPoint.IS_END){
            fromM = 0;
            toM = to.getMonthValue() - 1;
        }else{
            fromM = 0;
            toM = 0;
        }
        boolean keepGoing = true;
        if(ip.isStart && fromM <= toM){
            IterPoint newIp = IterPoint.make(true,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM++);
            if(m != null) keepGoing = m.iterateForward(from, to, newIp, predicate);
        }
        while(keepGoing && fromM <= toM){
            IterPoint newIP = IterPoint.make(false,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM++);
            if(m != null) keepGoing = m.iterateForward(from, to, newIP, predicate);
        }
        return keepGoing;
    }

    /**
     * Itera sobre os elementos de um ano por ordem cronológica inversa.
     * @param from A data de início.
     * @param to A data do fim.
     * @param ip Ponto em que está a iteração.
     * @param predicate Função a aplicar a todos os elementos.
     * @return {@code true} se a iteração deve continuar, {@code false} caso contrário.
     */
    boolean iterateBackwards(LocalDate from, LocalDate to, IterPoint ip, Predicate<T> predicate){
        int fromM;
        int toM;
        if(ip == IterPoint.IS_BOTH){
            fromM = from.getMonthValue() - 1;
            toM = to.getMonthValue() - 1;
        }else if(ip == IterPoint.IS_START){
            fromM = from.getMonthValue() - 1;
            toM = 0;
        }else if(ip == IterPoint.IS_END){
            fromM = 11;
            toM = to.getMonthValue() - 1;
        }else{
            fromM = 11;
            toM = 0;
        }
        boolean keepGoing = true;
        if(ip.isStart && fromM >= toM){
            IterPoint newIp = IterPoint.make(true,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM--);
            if(m != null) keepGoing = m.iterateBackwards(from, to, newIp, predicate);
        }
        while(keepGoing && fromM >= toM){
            IterPoint newIp = IterPoint.make(false,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM--);
            if(m != null) keepGoing = m.iterateBackwards(from, to, newIp, predicate);
        }
        return keepGoing;
    }

    /**
     * Conta o número de elementos do ano.
     * @param from A data de início.
     * @param to A data do fim.
     * @param ip Ponto em que está a iteração.
     * @return O número de elementos do ano.
     */
    long countElements(LocalDate from, LocalDate to, IterPoint ip){
        int fromM;
        int toM;
        if(ip == IterPoint.IS_BOTH){
            fromM = from.getMonthValue() - 1;
            toM = to.getMonthValue() - 1;
        }else if(ip == IterPoint.IS_START){
            fromM = from.getMonthValue() - 1;
            toM = 11;
        }else if(ip == IterPoint.IS_END){
            fromM = 0;
            toM = to.getMonthValue() - 1;
        }else{
            fromM = 0;
            toM = 0;
        }
        long count = 0;
        if(ip.isStart && fromM <= toM){
            IterPoint newIp = IterPoint.make(true,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM++);
            if(m != null) count += m.countElements(from, to, newIp);
        }
        while(fromM <= toM){
            IterPoint newIp = IterPoint.make(false,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM++);
            if(m != null) count += m.countElements(from, to, newIp);
            fromM++;
        }
        return count;
    }
}