# **ESP8266, MPU6050 & AdaFruit IO ile  Adım, Mesafe & Kalori Sayacı**

Bu proje, bir ESP8266 kartı, MPU6050 ivmeölçer ve Adafruit IO platformunu kullanarak adım, mesafe ve kalori sayımı yapar.

## **Adafruit IO Panosu**

Proje, Adafruit IO üzerinde adım, mesafe ve kalori verilerini görselleştirmek için bir pano oluşturmanıza olanak tanır.

<img src="https://github.com/ciftciyakup/esp8266-step_counter/blob/main/io.adafruit.com_yakupciftci_dashboards_adim-sayaci.png">

## **Proje Yapısı**

* .gitattributes: Git özniteliklerinin yapılandırması.  
* README.md: Proje hakkında bilgi veren bu dosya.  
* config.h: Wi-Fi ve Adafruit IO kimlik bilgilerini içeren yapılandırma dosyası.  
* esp8266\_stepcounter.ino: Projenin ana Arduino kodu.  
* io.adafruit.com\_yakupciftci\_dashboards\_adim-sayaci.png: Adafruit IO panosunun ekran görüntüsü.

## **Kullanılan Donanım**

* ESP8266 geliştirme kartı  
* MPU6050 ivmeölçer ve jiroskop modülü

## **Gerekli Kütüphaneler**

Bu projenin derlenebilmesi için aşağıdaki Arduino kütüphanelerine ihtiyacınız vardır:

* **Adafruit MPU6050 Kütüphanesi**: MPU6050 sensöründen veri okumak için kullanılır.  
* **Adafruit Unified Sensor Kütüphanesi**: Adafruit sensör kütüphaneleri için temel sınıfı sağlar.  
* **Wire Kütüphanesi**: I2C iletişimi için kullanılır.  
* **Adafruit IO Arduino Kütüphanesi**: Adafruit IO platformuyla iletişim kurmak için kullanılır.

## **Yapılandırma (config.h)**

config.h dosyası, Adafruit IO ve Wi-Fi bağlantınız için önemli bilgileri içerir. Projeyi kullanmadan önce bu değerleri kendi bilgilerinizle güncellemeniz gerekmektedir:

* IO\_USERNAME: Adafruit IO kullanıcı adınız.  
* IO\_KEY: Adafruit IO anahtarınız.  
* WIFI\_SSID: Wi-Fi ağınızın adı (SSID).  
* WIFI\_PASS: Wi-Fi ağınızın şifresi.

Örnek config.h içeriği:

\#define IO\_USERNAME "yakupciftci" //  
\#define IO\_KEY "aio\_nQhc30cDco3" //  
\#define WIFI\_SSID "laptop" //  
\#define WIFI\_PASS "yakup123" //

## **Çalışma Mantığı (esp8266\_stepcounter.ino)**

Proje, MPU6050 sensöründen ivme verilerini okur ve y eksenindeki ivme değişimlerini algılayarak adım sayar. Her 3 saniyede bir, toplanan adım sayısı, hesaplanan mesafe ve yakılan kalori Adafruit IO'ya gönderilir.

* **Adım Sayma**: Y ekseni ivmesi belirli bir eşiği (a.acceleration.y \> 1\) aştığında bir adım olarak sayılır.  
* **Mesafe Hesaplama**: Toplam adım sayısı, distanceinonestep (adım başına santimetre cinsinden mesafe) değeri ile çarpılarak mesafe (metre cinsinden) hesaplanır.  
* **Kalori Hesaplama**: Yakılan kalori, steps \* 0.05 formülü ile basitçe hesaplanır.  
* **Adafruit IO Entegrasyonu**:  
  * adim-sayaci beslemesine adım sayısı gönderilir.  
  * mesafe beslemesine hesaplanan mesafe gönderilir.  
  * kalori beslemesine yakılan kalori gönderilir.  
  * mesafe-al beslemesinden bir hedef mesafe (range) alınabilir. Eğer hesaplanan mesafe bu hedefe ulaşırsa "Hedefinize ulaştınız" mesajı seri monitöre yazdırılır.

## **Kurulum ve Çalıştırma**

1. Yukarıda belirtilen kütüphaneleri Arduino IDE'nize yükleyin.  
2. config.h dosyasındaki Wi-Fi ve Adafruit IO bilgilerinizi güncelleyin.  
3. ESP8266 kartınızı bilgisayarınıza bağlayın.  
4. Arduino IDE'den doğru kartı ve bağlantı noktasını seçin.  
5. esp8266\_stepcounter.ino dosyasını derleyin ve ESP8266 kartınıza yükleyin.  
6. Seri Monitörü açarak bağlantı durumunu ve sensör okumalarını takip edebilirsiniz.
