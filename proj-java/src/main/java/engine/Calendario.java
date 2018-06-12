package engine;

import engine.collections.SortedLinkedList;

import java.time.LocalDate;
import java.util.*;
import java.util.function.Predicate;

/**
 * Classe que define o calendário.
 *
 * @param <T> Tipo dos elementos guardados.
 */
public class Calendario<T extends Chronological> {

    /** Anos de um calendário. */
    private final Map<LocalDate,SortedLinkedList<T>> elems;
    private final TreeSet<LocalDate> keys;

    /**
     * Cria um calendário.
     */
    public Calendario(){
        this.elems = new HashMap<>();
        this.keys = new TreeSet<>();
    }

    /**
     * Adiciona um elemento no calendário.
     *
     * @param c Elemento a adicionar.
     */
    public void addElem(T c){
        LocalDate date = c.getDate().toLocalDate();
        SortedLinkedList<T> list = this.elems.get(date);
        if(list == null){
            list = new SortedLinkedList<>(Comparator.comparing(Chronological::getDate));
            this.elems.put(date, list);
            this.keys.add(date);
        }
        list.add(c);
    }

    /**
     * Itera o calendário dentro de um intervalo de tempo.
     *
     * @param from      A data de início.
     * @param to        A data do fim.
     * @param predicate Função a aplicar a todos os elementos.
     */
    public void iterate(LocalDate from, LocalDate to, Predicate<T> predicate){
        if(from.isBefore(to)) iterateForward(from, to, predicate);
        else iterateBackwards(from, to, predicate);
    }

    /**
     * Itera sobre os elementos de um calendário por ordem cronológica.
     *
     * @param from      A data de início.
     * @param to        A data do fim.
     * @param predicate Função a aplicar a todos os elementos.
     */
    private void iterateForward(LocalDate from, LocalDate to, Predicate<T> predicate){
        LocalDate fromK = this.keys.ceiling(from);
        LocalDate toK = this.keys.floor(to);
        NavigableSet<LocalDate> localDates = this.keys.subSet(fromK, true, toK, true);
        for(LocalDate d : localDates){
            for(T t : this.elems.get(d)){
                if(!predicate.test(t)) return;
            }
        }
    }

    /**
     * Itera sobre os elementos de um calendário por ordem cronológica inversa.
     *
     * @param from      A data de início.
     * @param to        A data do fim.
     * @param predicate Função a aplicar a todos os elementos.
     */
    private void iterateBackwards(LocalDate from, LocalDate to, Predicate<T> predicate){
        LocalDate fromK = this.keys.ceiling(to);
        LocalDate toK = this.keys.floor(from);
        NavigableSet<LocalDate> localDates = this.keys.subSet(fromK, true, toK, true);
        Iterator<LocalDate> iterator = localDates.descendingIterator();
        while(iterator.hasNext()){
            LocalDate d = iterator.next();
            Iterator<T> iterator1 = this.elems.get(d).descendingIterator();
            while(iterator1.hasNext()){
                T t = iterator1.next();
                if(!predicate.test(t)) return;
            }
        }
    }

    /**
     * Conta o número de elementos do calendário.
     *
     * @param from A data de início.
     * @param to   A data do fim.
     * @return O número de elementos.
     */
    public long countElements(LocalDate from, LocalDate to){
        LocalDate fromK = this.keys.ceiling(from);
        LocalDate toK = this.keys.floor(to);
        NavigableSet<LocalDate> localDates = this.keys.subSet(fromK, true, toK, true);
        long count = 0;
        for(LocalDate d : localDates){
            count += this.elems.get(d).size();
        }
        return count;
    }
}
