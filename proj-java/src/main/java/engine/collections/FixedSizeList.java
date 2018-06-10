package main.java.engine.collections;

import java.util.ArrayList;
import java.util.List;

public class FixedSizeList<T> {

    private final int maxSize;
    private final List<T> list;

    public FixedSizeList(int maxSize){
        this.maxSize = maxSize;
        this.list = new ArrayList<>(maxSize);
    }

    private void boundsCheck(int idx){
        if(idx >= this.maxSize) throw new ArrayIndexOutOfBoundsException(idx);
    }

    private void nullFill(int idx){
        int size = this.list.size();
        if(idx >= size)
            for(int i = size; i < idx + 1; i++)
                this.list.add(null);
    }

    public T get(int index){
        boundsCheck(index);
        if(index >= this.list.size()) return null;
        else return this.list.get(index);
    }

    public void set(int index, T element){
        boundsCheck(index);
        nullFill(index);
        this.list.set(index, element);
    }
}
