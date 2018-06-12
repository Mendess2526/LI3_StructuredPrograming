package engine.calendario;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Predicate;

/**
 * Classe que define o calendário.
 * @param <T> Tipo dos elementos guardados.
 */
public class Calendario<T extends Chronological> {
    /** Anos de um calendário. */
    private final Map<Integer,Year<T>> years;

    /**
     * Cria um calendário.
     */
    public Calendario(){
        this.years = new HashMap<>();
    }

    /**
     * Adiciona um elemento no calendário.
     * @param c Elemento a adicionar.
     */
    public void addElem(T c){
        this.years.computeIfAbsent(c.getDate().getYear(), k->new Year<>()).addElem(c);
    }

    /**
     * Itera o calendário dentro de um intervalo de tempo.
     * @param from A data de início.
     * @param to A data do fim.
     * @param predicate Função a aplicar a todos os elementos.
     */
    public void iterate(LocalDate from, LocalDate to, Predicate<T> predicate){
        if(from.isBefore(to)) iterateForward(from, to, predicate);
        else iterateBackwards(from, to, predicate);
    }

    /**
     * Itera sobre os elementos de um calendário por ordem cronológica.
     * @param from A data de início.
     * @param to A data do fim.
     * @param predicate Função a aplicar a todos os elementos.
     */
    private void iterateForward(LocalDate from, LocalDate to, Predicate<T> predicate){
        int fromY = from.getYear();
        int toY = to.getYear();
        boolean keepGoing = true;
        if(fromY <= toY){
            IterPoint ip = IterPoint.make(true, fromY == toY);
            Year<T> y = this.years.get(fromY++);
            if(y!=null) keepGoing = y.iterateForward(from, to, ip, predicate);
        }
        while(keepGoing && fromY <= toY){
            IterPoint ip = IterPoint.make(false, fromY == toY);
            Year<T> y = this.years.get(fromY++);
            if(y!=null) keepGoing = y.iterateForward(from, to, ip, predicate);
        }
    }

    /**
     * Itera sobre os elementos de um calendário por ordem cronológica inversa.
     * @param from A data de início.
     * @param to A data do fim.
     * @param predicate Função a aplicar a todos os elementos.
     */
    private void iterateBackwards(LocalDate from, LocalDate to, Predicate<T> predicate){
        int fromY = from.getYear();
        int toY = to.getYear();
        boolean keepGoing = true;
        if(fromY >= toY){
            IterPoint ip = IterPoint.make(true, fromY == toY);
            Year<T> y = this.years.get(fromY--);
            if(y!=null) keepGoing = y.iterateBackwards(from, to, ip, predicate);
        }
        while(keepGoing && fromY >= toY){
            IterPoint ip = IterPoint.make(false, fromY == toY);
            Year<T> y = this.years.get(fromY--);
            if(y!=null) keepGoing = y.iterateBackwards(from, to, ip, predicate);
        }
    }

    /**
     * Conta o número de elementos do calendário.
     * @param from A data de início.
     * @param to A data do fim.
     * @return O número de elementos.
     */
    public long countElements(LocalDate from, LocalDate to){
        if(from.isAfter(to)){
            LocalDate tmp = from;
            from = to;
            to = tmp;
        }
        int fromY = from.getYear();
        int toY = to.getYear();
        long count = 0;
        if(fromY <= toY){
            IterPoint ip = IterPoint.make(true, fromY == toY);
            Year<T> y = this.years.get(fromY++);
            if(y != null) count = y.countElements(from, to, ip);
        }
        while(fromY <= toY){
            IterPoint ip = IterPoint.make(false, fromY == toY);
            Year<T> y = this.years.get(fromY++);
            if(y!=null) count += y.countElements(from, to, ip);
        }
        return count;
    }
}
