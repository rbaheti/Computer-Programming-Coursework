package lab10;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class SetSorting<T> {

    public void Sort(T[] unsorted) {
        for (int outer = 1; outer < unsorted.length; outer++) {
            for (int inner = 0; inner < (unsorted.length - outer); inner++) {
                if ((((Comparable) (unsorted[inner])).compareTo(unsorted[inner + 1])) > 0) {
                    T tmp = unsorted[inner];
                    unsorted[inner] = unsorted[inner + 1];
                    unsorted[inner + 1] = tmp;
                }
            }
        }
    }

public void Display(T[] unsorted) {
        for (T i : unsorted) {
            System.out.println(i + " ");
        }
        System.out.println();
    }
}
