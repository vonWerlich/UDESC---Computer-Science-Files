package persistencia;

import java.util.List;
import java.util.Set;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBObject;
import com.mongodb.MongoClient;
import com.mongodb.client.MongoDatabase;
import com.mongodb.connection.Connection;
import com.mongodb.DBCursor;

public class Conexao {

	
	@SuppressWarnings("deprecation")
	public static Connection getConexao () {
		
		MongoClient mongoClient = new MongoClient("localhost", 27017);
		
		return (Connection) mongoClient;


	}
}