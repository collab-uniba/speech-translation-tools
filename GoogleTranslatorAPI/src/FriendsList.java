import java.util.Collections;
import java.util.Vector;

import com.skype.ContactList;
import com.skype.Friend;
import com.skype.Skype;
import com.skype.SkypeException;

public class FriendsList {
	
	public FriendsList() {};

	public Friend[] getAllFriends() throws SkypeException, InterruptedException {
		// Get all skype friends of a user.
		ContactList list = Skype.getContactList();
	
		Friend fr[] = list.getAllFriends();
		// Printing the number of friends user has.
		System.out.println(fr.length);
		
		for(int i=0; i < fr.length; i++)
		{
			Friend f = fr[i];
			//Getting the friends ID
			System.out.println("Friend ID :" + f.getId());
		}
		return fr;
	}
	
	public Vector<String> getFriendsIdsAsString() throws SkypeException, InterruptedException {
		Vector<String> nomesDosAmigos = new Vector<String>();
		
		ContactList list = Skype.getContactList();
		
		Friend fr[] = list.getAllFriends();
		
		for(int i=0; i < fr.length; i++)
		{
			nomesDosAmigos.add(fr[i].getId());
			Collections.sort(nomesDosAmigos);
		}
		return nomesDosAmigos;
	}
	
	public static int getNumberOfFriends() throws SkypeException {
		ContactList list = Skype.getContactList();
		Friend fr[] = list.getAllFriends();
		return fr.length + 1;
	}
}



