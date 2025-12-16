package teste;

import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.MongoDatabase;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.bson.Document;

import com.mongodb.BasicDBObject;
import com.mongodb.DBCollection;
import com.mongodb.DBObject;
import com.mongodb.MongoClient; 
import com.mongodb.MongoCredential;  

public class ConnectToDB { 
   
   public static void main( String args[] ) {  
      
      // Creating a Mongo client 
      MongoClient mongo = new MongoClient( "localhost" , 27017 ); 
   
      // Creating Credentials 
      MongoCredential credential; 
      credential = MongoCredential.createCredential("sampleUser", "myDb", "password".toCharArray()); 
      //System.out.println("Connected to the database successfully");  
      
      // Accessing the database 
      MongoDatabase database = mongo.getDatabase("universidade"); 
      //System.out.println("Credentials ::"+ credential);   

      //Creating a collection 
      //database.createCollection("sampleCollection"); 
      //System.out.println("Collection created successfully"); 
      
      MongoCollection<Document> coll = database.getCollection("pessoa");
      Document document = new Document("id", "1")
    			.append("nome", "Maria")
    			.append("idade", 23);
    			
      coll.insertOne(document);
      
      /*MongoCollection<Document> collection = database.getCollection("pessoa");
		System.out.println("Collection selected successfully");
		List<Document> list = new ArrayList<Document>();

		collection.insertMany(list);
		// Getting the iterable object
		FindIterable<Document> iterDoc = collection.find();
		int i = 1;
		// Getting the iterator
		MongoCursor<Document> it = iterDoc.iterator();
		while (it.hasNext()) {
			System.out.println(it.next());
			i++;
		}*/
   } 
}
