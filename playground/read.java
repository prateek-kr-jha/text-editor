import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class read {
    public static void main(String[] args) {
        try {
            String fileName = "hello.txt";
                   FileReader fileReader = new FileReader(fileName);
                BufferedReader bufferedReader = new BufferedReader(fileReader);
    
                String line;
                // Read the file line by line
                while ((line = bufferedReader.readLine()) != null) {
                    System.out.println(line);
                }
    
                // Close the file
                bufferedReader.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}