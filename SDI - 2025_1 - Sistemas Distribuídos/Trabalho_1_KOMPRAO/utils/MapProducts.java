package utils;

import java.util.Iterator;
import java.util.HashMap;
import java.util.Map;

public class MapProducts {
    private Map<String, Products> mapProducts = new HashMap<String, Products>();

    public MapProducts() {}

    public boolean contains_key(String id) {
        return mapProducts.containsKey(id);
    }

    public boolean part_key_exists(String id) {
        String[] id_array = id.split(":");

        for (String key : mapProducts.keySet()) {
            String[] key_array = key.split(":");
            
            if (id_array[1].equals(key_array[1])){
                if(!id_array[0].equals(key_array[0])){
                    return true;
                }
            }

        }
        System.out.println();

        return false;
    }

    public double get_total_value_list(String id) throws NullPointerException {
        if (mapProducts.containsKey(id)) {
            return get_list(id).getTotalValue();
        }

        throw new NullPointerException("Id inexistente");
    }


    public boolean new_list(String id) {
        if (mapProducts.containsKey(id)) {
            return false;
        }

        mapProducts.put(id, new Products());
        return true;
    }

    public Products get_list(String id) throws NullPointerException {
        if (mapProducts.containsKey(id)) {
            return mapProducts.get(id);
        }

        throw new NullPointerException("Id inexistente");
    }

    public void remove_list(String id) throws NullPointerException {
        if (mapProducts.containsKey(id)) {
            mapProducts.remove(id);
        }else{
            throw new NullPointerException("Id: " + id + " inexistente");
        }
    }

    public void add(String id, Product item) throws NullPointerException, Exception {
        System.out.println(mapProducts.containsKey(id));
        if (mapProducts.containsKey(id)) {
            Products p = mapProducts.get(id);            
            p.add(item);
        }else{
            throw new NullPointerException("Id: " + id + " inexistente");
        }
    }

    @Override
    public String toString() {
        String res = "";

        Iterator<Map.Entry<String, Products>> iterator =  mapProducts.entrySet().iterator();

        while (iterator.hasNext()) {
            Map.Entry<String, Products> pair = iterator.next();
            res += "cpf: " + pair.getKey() + "\nProdutos:\n" + pair.getValue() + "\n";
        }

        return res;
    }
}
