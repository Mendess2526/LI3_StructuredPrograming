package main.java.engine.collections;

import java.util.ArrayList;
import java.util.List;

public class FixedSizeList<T> {

    private final Object[] list;

    public FixedSizeList(int size){
        this.list = new Object[size];
    }

    @SuppressWarnings("unchecked")
    public T get(int index){
        return (T) this.list[index];
    }

    public void set(int index, T element){
        this.list[index] = element;
    }
}
