import java.util.*;
import java.util.Map.Entry;

public class HashMapMemUsage {

    public HashMap<String, String> map;

    public HashMapMemUsage() {
        map = new HashMap<String, String>();
    }

    private long mem_used() {
        return Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
    }

    private int to_MiB(long bytes) {
        return (int) (bytes >> 20);
    }

    private int populate(int memoryGoalPerIter) {
        int pre_usage = to_MiB(mem_used());
        int goal_to_reach = pre_usage + memoryGoalPerIter;
        int total_added =0;
        while (goal_to_reach >= to_MiB(mem_used())) {
            int random_add = (int) (Math.random() * 1000);
            for (int i = 0; i < random_add; i++) {
                String key = UUID.randomUUID().toString().replace("-", "");
                String value = UUID.randomUUID().toString();
                map.put(key, value);
            }
            total_added += random_add;
        }
        return total_added;
    }

    private int depopulate() {
        int size = map.size();

        int to_remove = (int) (Math.random() * size * 0.1);

        int count = 0;
        Iterator<Entry<String, String>> it = map.entrySet().iterator();
        ArrayList<String> keys_to_remove = new ArrayList<String>();
        while (count < to_remove && it.hasNext()) {
            String key_to_remove = it.next().getKey();
            boolean removed = Math.random() < 0.5 ? true : false;
            if (removed) {
                keys_to_remove.add(key_to_remove);
                count++;
            }
        }

        keys_to_remove.forEach((k) -> map.remove(k));
        return to_remove;
    }

    public void run(int count, int memGoalMiB) {
        int curr_iter = 0;
        int curr_mem_mib = 0;

        while (curr_iter < count || curr_mem_mib < memGoalMiB) {
            int added = populate(memGoalMiB / count);
            curr_mem_mib = to_MiB(mem_used());
            curr_iter++;
            System.out.println("Iter " + curr_iter + " Added " + added + " Mem = " + curr_mem_mib);
            int dropped = depopulate();
            curr_mem_mib = to_MiB(mem_used());
            System.out.println("Dropped " + dropped + " Drop Mem = " + curr_mem_mib);
        }

    }

    public static void main(String[] args) throws Exception {
        int iteration_count = 10;
        int memGoalMiB = 1000;
        if (args.length != 0)
            iteration_count = Integer.parseInt(args[0]);
        if (args.length == 2) {
            memGoalMiB = Integer.parseInt(args[1]);
        }
        HashMapMemUsage a = new HashMapMemUsage();

        a.run(iteration_count, memGoalMiB);
    }
}
