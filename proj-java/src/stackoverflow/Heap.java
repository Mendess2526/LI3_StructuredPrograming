package stackoverflow;

import java.util.Arrays;
import java.util.Comparator;

public class Heap<T> {
    private Object[] v;
    private Comparator<T> c;
    private int load;

    public Heap(int size, Comparator<T> c){
        this.v = new Object[size+1];
        this.c = c;
        this.load = 0;
    }

    @SuppressWarnings("unchecked")
    private T index(int idx){
        return (T) this.v[idx];
    }

    private void swap(int a, int b){
        Object t = this.v[a];
        this.v[a] = this.v[b];
        this.v[b] = t;
    }

    public void add(T a){
        this.v[this.load] = a;
        bubbleUp(this.load);
        if(this.load < this.v.length - 1) this.load++;
        else if(this.c.compare(index(this.load - 1), index(this.load)) > 0)
            swap(this.load - 1, this.load);
    }

    public T remove(){
        if(this.load == 0) throw new ArrayIndexOutOfBoundsException(0);
        T r = index(0);
        swap(0, --this.load);
        bubbleDown();
        return r;
    }

    private void bubbleUp(int idx){
        while(idx != 0 && this.c.compare(index((idx-1)/2),index(idx)) > 0){
            swap((idx-1)/2, idx);
            idx = (idx - 1) / 2;
        }
    }

    private void bubbleDown(){
        int f = 1;
        int i = 0;
        while(f < this.load){
            if((f + 1 < this.load) && this.c.compare(index(f + 1), index(f)) < 0)
                f = f + 1;
            if(this.c.compare(index(i), index(f)) <= 0) return;
            swap(i, f);
            i = f;
            f = 2 * i + 1;
        }
    }

    @Override
    public String toString(){
        return "Heap{" +
                "v=" + Arrays.toString(v)
                + ", c=" + c
                + ", load=" + load
                + '}';
    }
}
