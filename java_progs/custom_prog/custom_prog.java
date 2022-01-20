import java.util.*;

class CustomProg {
    public static void main (String[] arg){
        int[] int_array = {1, 2, 3, 4, 5};
        System.out.println(int_array[0]);
        int_arr_operation(int_array);

    }

    public static void int_arr_operation (int[] arr) {
        Random rand = new Random();
        while (true){
            for (int i = 0; i < arr.length; i++) {
                arr[i] = rand.nextInt(1000);
                try {
                    Thread.sleep(50);
                } catch (InterruptedException e){
                    System.out.println("Interreupted...");
                }
            }
            System.out.println(Arrays.toString(arr));
        }
    }

}