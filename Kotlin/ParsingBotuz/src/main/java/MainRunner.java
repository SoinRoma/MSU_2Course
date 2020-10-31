import org.telegram.telegrambots.meta.api.methods.send.SendPhoto;
import java.util.ArrayList;

public class MainRunner
{
    public static void main(String[] args)
    {
        while (true)
        {
            Bot bot = new Bot();
            ParsingClass parsed = new ParsingClass("https://wallpaperscraft.ru/"); // "https://wallpaperscraft.ru/"
            ArrayList<String> mas = parsed.getMas();
           // ArrayList<String> masfortegi = parsed.getMasfortegi();
            //ArrayList<String> postedmasfortegi = new ArrayList<String>();
            ArrayList<String> postedMas = new ArrayList<String>();
            for (String item : mas) {      //цикл проверки нового массива на совпадение
                if (postedMas.contains(item)) {
                    mas.remove(item);
                }
            }
           // for (String item2 : masfortegi) {      //цикл проверки нового массива на совпадение
                //if (postedMas.contains(item2)) {
              //      masfortegi.remove(item2);
              //  }
           // }
           // int i=0;
            for (String item : mas)  //цикл отправки фото
            {

                SendPhoto sendPhoto = new SendPhoto();
                sendPhoto.setChatId("-1001299029139"); //айди канала куда бот будет скидывать фото
                sendPhoto.setPhoto(item);
               // sendPhoto.getCaption();
               // i++;
                bot.sendPhoto(sendPhoto);
                System.out.println(item);
                postedMas.add(item);
            }

            try  //каждый час делать проверку сайта
            {
                Thread.sleep(3600000);
            }
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }

    }
}
