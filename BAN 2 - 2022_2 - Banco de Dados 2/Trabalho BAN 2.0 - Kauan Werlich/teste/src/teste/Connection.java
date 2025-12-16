package teste;

import java.util.List;
import java.util.Set;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBObject;
import com.mongodb.MongoClient;
import com.mongodb.DBCursor;



public class Connection {
	
	
	public static void main(String[] args) {
	
		MongoClient mongoClient = new MongoClient("localhost", 27017);
		List<String> databases = mongoClient.getDatabaseNames();
       
		for (String dbName : databases) {
            System.out.println("- Database: " + dbName);
            DB db = mongoClient.getDB(dbName);
            
            Set<String> collections = db.getCollectionNames();
            for (String colName : collections) {
                System.out.println("\t + Collection: " + colName);
            }
        }
        
        DB db = mongoClient.getDB("teste");
        DBCollection coll = db.getCollection("Pessoas");
        DBObject data = new BasicDBObject();
        data.put("cpf", "3243248"); 
        data.put("nome", "Antonio"); 
        data.put("endereco", "Rua Otto Benack"); 
        coll.insert(data);
        
        
        BasicDBObject query = new BasicDBObject("nome", "Fabiano");
        DBCursor cursor = coll.find(query);
		try {
			 while(cursor.hasNext()) {
				 System.out.println(cursor.next());
			 }
		} finally {
			cursor.close();
		}


	}
	

}
