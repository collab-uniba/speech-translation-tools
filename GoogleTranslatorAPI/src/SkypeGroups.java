import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

import com.skype.Chat;
import com.skype.Skype;
import com.skype.SkypeException;
import com.skype.connector.Connector;
import com.skype.connector.ConnectorException;



//DO NOT RUN THE CLASS AND CLOSE APPLICATION OR WILL HANG THE SKYPE.
// STILL WORKING

public class SkypeGroups {

	private Chat chatEmGrupo = null;
	
	static {
		Connector.useJNIConnector(true);
	}
	
	public static void main(String args[]) throws Exception {
		
		SkypeGroups skypeGroups = new SkypeGroups();
		skypeGroups.connect();
		
		String text = "";
		String option = "";
		boolean closeGroup = false;
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Enter a friend id to create a chat:");
		
		ArrayList<String> idsList = new ArrayList<String>();
		
		option = br.readLine();
		int groupSize = 0;
		idsList.add(option);
		
		//System.out.println(idsList.size());
		
		groupSize++;
		while(closeGroup == false) {
			System.out.println("Do you want to add more friends? (y/n)");
			option = br.readLine();
			
			if(option.toLowerCase().equals("n")) {
				closeGroup = true;
			} else {
				System.out.println("Enter another friend id:");
				idsList.add(br.readLine());
				groupSize++;
			}
		}
		System.out.println("Creating chat... ");
		System.out.print("> ");
		String skypeIds[] = new String[groupSize];
		
		for(int i = 0; i < idsList.size(); i++) {
			skypeIds[i] = idsList.get(i);
			//System.out.println(skypeIds);
		}
		//TODO close connections on exit.
		
		while (true) {
			text = br.readLine();
			skypeGroups.sendMessage(skypeIds, text);
		}
	}
	
	private void sendMessage(String ids[], String text) throws SkypeException {
		chatEmGrupo = (Chat) (null == chatEmGrupo ? Skype.chat(ids) : chatEmGrupo);
		chatEmGrupo.send(text);
	}
	
	public void connect() throws Exception {
		Connector.Status status = null;
		Connector con = Connector.getInstance();
		
		try {
			status = con.connect();
		} catch (ConnectorException e1) {
			e1.printStackTrace();
			throw new Exception(e1.getMessage());
		}

		if (status != Connector.Status.ATTACHED) {
			throw new Exception(new Exception("Please install Skype from www.skype.com and run it."));
		}
		System.out.println("Connected, Skype ver. " + Skype.getVersion());
	}
}
