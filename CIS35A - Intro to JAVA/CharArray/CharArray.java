package chararray;
import java.util.*;
import java.io.*;

public class CharArray {
    
    public static void main(String[] args) {
        System.out.println("Please enter characters from 'A' to 'E' upto 10  times or less");
        System.out.println("Please enter any other number or character, once done");
        
        char ch[] = new char[10];
        int count[] = new int[5];
        char mychar[] = new char[5];
        int size = 0;
        
        Scanner in = new Scanner(System.in);
        String line = in.nextLine();
        for (int i = 0; i < line.length(); i++)
        {
            ch[i] = line.charAt(i);
            if (ch[i] >= 'A' && ch[i] <= 'E')
		{			
                    count[ch[i] - 'A']++;
                    mychar[ch[i] - 'A'] = ch[i];
		}
            else if (ch[i] >= 'a' && ch[i] <= 'e')
                {			
                    count[ch[i] - 'a']++;
                    mychar[ch[i] - 'a'] = ch[i];
		}
            else if (ch[i] >= '0' && ch[i] <= '9')
                {			
                    count[ch[i] - '0']++;
                    mychar[ch[i] - '0'] = ch[i];
		}
            else
            {
                continue;
            }
        }

	for (int i = 0; i < 5; i++)
	{            
		for (int j = 0; j < count[i]; j++)
		{
			System.out.print(" " + mychar[i]);
		}
		System.out.println();
	}
        
    }
    
}
