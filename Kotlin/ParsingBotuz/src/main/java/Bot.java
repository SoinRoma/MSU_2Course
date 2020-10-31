import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.methods.send.SendPhoto;
import org.telegram.telegrambots.meta.api.objects.Update;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;

public class Bot extends TelegramLongPollingBot {    //бот зависим от лонгполингбот


    public void onUpdateReceived(Update update) {
  }
   //
    public String getBotUsername() {
        return "ParsingPhotos_bot";
    }

    public String getBotToken() {
        return "749676339:AAHdYVK5p8XehpPkF49sDzuRaKzt9sEcWQI";
    }

    public void sendPhoto(SendPhoto sendPhoto) //функция для отправки фото
    {
        try //попытайся отправить это
        {
            this.execute(sendPhoto);
        }
        catch (TelegramApiException e)  //если не получилось
        {
            e.printStackTrace();
        }
    }
}




