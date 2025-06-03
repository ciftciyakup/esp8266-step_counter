# ESP8266 Step, Distance & Kcal Counter with MPU6050 & AdaFruit IO

ESP8266 mikrodenetleyici, MPU6050 ivmeölçer sensörü ve AdaFruit IO platformu kullanılarak geliştirilmiş akıllı adım sayacı projesi. Gerçek zamanlı adım sayımı, mesafe hesaplama ve kalori yakımı takibi özelliklerine sahiptir.

## 📸 Ekran Görüntüleri

### AdaFruit IO Dashboard
<table>
  <tr>
    <td align="center">
      <img src="https://github.com/ciftciyakup/esp8266-step_counter/blob/main/io.adafruit.com_yakupciftci_dashboards_adim-sayaci.png" alt="AdaFruit IO Dashboard"/>
      <br><em>AdaFruit IO Dashboard - Gerçek Zamanlı Veri Görünümü</em>
    </td>
  </tr>
</table>

## 🚀 Özellikler

- **Gerçek Zamanlı Adım Sayımı**: MPU6050 ivmeölçer sensörü ile hassas adım algılama
- **Mesafe Hesaplama**: Kişiselleştirilebilir adım uzunluğu ile mesafe takibi
- **Kalori Hesaplama**: Adım sayısına dayalı kalori yakımı hesaplaması
- **IoT Bağlantısı**: AdaFruit IO platformu ile bulut tabanlı veri saklama
- **Hedef Belirleme**: AdaFruit IO üzerinden mesafe hedefi belirleme
- **WiFi Bağlantısı**: Kablosuz veri aktarımı
- **MQTT Protokolü**: Güvenilir ve hızlı veri iletişimi

## 🛠️ Kullanılan Teknolojiler

### Donanım
- **ESP8266** - WiFi özellikli mikrodenetleyici
- **MPU6050** - 6-eksen ivmeölçer ve jiroskop sensörü

### Yazılım
- **Arduino IDE** - Geliştirme ortamı
- **Adafruit MPU6050 Library** - Sensör kontrolü
- **AdafruitIO Library** - IoT platform entegrasyonu
- **AdaFruit IO Platform** - Bulut veri saklama ve görselleştirme

## 📦 Kurulum

### 1. Donanım Bağlantıları

**MPU6050 ↔ ESP8266 Bağlantı Şeması:**
```
MPU6050    ESP8266
VCC    →   3.3V
GND    →   GND
SCL    →   D1 (GPIO5)
SDA    →   D2 (GPIO4)
```

### 2. Yazılım Kurulumu

1. **Arduino IDE'yi kurun** ve ESP8266 board paketini ekleyin
2. **Gerekli kütüphaneleri yükleyin:**
   ```
   - Adafruit MPU6050 Library
   - Adafruit IO Arduino Library
   - Adafruit Sensor Library
   ```

3. **Projeyi klonlayın**
   ```bash
   git clone https://github.com/ciftciyakup/esp8266-step_counter.git
   cd esp8266-step_counter
   ```

4. **Konfigürasyon Ayarları**
   
   `config.h` dosyasını düzenleyin:
   ```c
   #define IO_USERNAME "your_adafruit_io_username"
   #define IO_KEY "your_adafruit_io_key"
   #define WIFI_SSID "your_wifi_ssid"
   #define WIFI_PASS "your_wifi_password"
   ```

5. **AdaFruit IO Hesabı Oluşturun**
   - [io.adafruit.com](https://io.adafruit.com) adresinden hesap açın
   - Aşağıdaki feed'leri oluşturun:
     - `adim-sayaci` (adım sayısı)
     - `mesafe` (mesafe)
     - `kalori` (kalori)
     - `mesafe-al` (hedef mesafe)

6. **Kodu ESP8266'ya yükleyin**

## 📁 Proje Yapısı

```
esp8266-step_counter/
├── config.h                                    # WiFi ve AdaFruit IO ayarları
├── esp8266_stepcounter.ino                    # Ana program kodu
├── io.adafruit.com_yakupciftci_dashboards_adim-sayaci.png  # Dashboard görüntüsü
├── .gitattributes                             # Git yapılandırması
└── README.md                                  # Proje dokümantasyonu
```

## 🎯 Kullanım

### Başlangıç
1. ESP8266'yı power supply ile besleyin
2. Cihaz otomatik olarak WiFi'ye bağlanacak ve AdaFruit IO ile senkronize olacak
3. MPU6050 sensörü kalibre edildikten sonra adım sayımı başlayacak

### Konfigürasyon
- **Adım Uzunluğu**: `distanceinonestep` değişkenini kendi adım uzunluğunuza göre ayarlayın (cm cinsinden)
- **Hedef Mesafe**: AdaFruit IO dashboard üzerinden `mesafe-al` feed'ini kullanarak hedef belirleyin

### Veri Takibi
- **Adım Sayısı**: Her adım otomatik olarak sayılır ve 3 saniyede bir güncellenir
- **Mesafe**: Adım sayısı × adım uzunluğu formülü ile hesaplanır
- **Kalori**: Adım sayısı × 0.05 formülü ile yaklaşık kalori hesaplanır

## 📊 Veri Akışı

```
MPU6050 Sensör → ESP8266 → WiFi → AdaFruit IO → Dashboard
```

1. **Sensör Okuma**: MPU6050'den Y-eksen ivme değeri okunur
2. **Adım Algılama**: İvme değeri 1g'yi aştığında adım sayılır
3. **Hesaplamalar**: Mesafe ve kalori değerleri hesaplanır
4. **Veri Gönderimi**: 3 saniyede bir AdaFruit IO'ya gönderilir
5. **Dashboard Güncellemesi**: Gerçek zamanlı görselleştirme

## ⚙️ Teknik Detaylar

### Sensör Ayarları
- **İvmeölçer Aralığı**: ±8G
- **Jiroskop Aralığı**: ±500 deg/s
- **Filtre Bant Genişliği**: 21 Hz

### Algoritma
- **Adım Algılama**: Y-eksen ivme değeri > 1g threshold
- **Debounce**: 350ms bekleme süresi (çift sayım önleme)
- **Güncelleme Aralığı**: 3 saniye

### İletişim
- **WiFi**: 2.4GHz
- **Protokol**: MQTT over SSL
- **Veri Formatı**: JSON

## 🔧 Kalibrasyon

1. **Adım Uzunluğu Ölçümü**:
   - 10 adım atın ve mesafeyi ölçün
   - Toplam mesafeyi 10'a bölün
   - `distanceinonestep` değişkenini güncelleyin

2. **Sensör Kalibrasyonu**:
   - Cihazı düz yüzeyde sabit tutun
   - Serial Monitor'den baseline değerleri gözlemleyin
   - Gerekirse threshold değerini ayarlayın

## 🤝 Katkıda Bulunma

1. Bu repository'yi fork edin
2. Feature branch oluşturun (`git checkout -b feature/YeniOzellik`)
3. Değişikliklerinizi commit edin (`git commit -am 'Yeni özellik eklendi'`)
4. Branch'inizi push edin (`git push origin feature/YeniOzellik`)
5. Pull Request oluşturun

## 🔧 Sorun Giderme

### WiFi Bağlantı Sorunları
- SSID ve şifrenin doğru olduğundan emin olun
- 2.4GHz ağ kullandığınızdan emin olun
- Router'ın ESP8266'yı desteklediğini kontrol edin

### Sensör Sorunları
- I2C bağlantılarını kontrol edin
- 3.3V besleme voltajını doğrulayın
- Serial Monitor'den hata mesajlarını inceleyin

### AdaFruit IO Bağlantı Sorunları
- Username ve Key'in doğru olduğundan emin olun
- Feed isimlerinin eşleştiğini kontrol edin
- Internet bağlantısını test edin

## 📄 Lisans

Bu proje MIT lisansı altında lisanslanmıştır.

## 👨‍💻 Geliştirici

**Yakup Çiftçi**
- GitHub: [@ciftciyakup](https://github.com/ciftciyakup)
- LinkedIn: [yakup-ciftci](https://www.linkedin.com/in/yakup-ciftci/)

## 🙏 Teşekkürler

- [Adafruit](https://www.adafruit.com/) - MPU6050 kütüphanesi ve IoT platformu
- [ESP8266 Community](https://github.com/esp8266/Arduino) - ESP8266 Arduino Core
- [Arduino](https://www.arduino.cc/) - Geliştirme ortamı

## 📚 Kaynaklar

- [MPU6050 Datasheet](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)
- [ESP8266 Documentation](https://arduino-esp8266.readthedocs.io/)
- [AdaFruit IO Documentation](https://learn.adafruit.com/welcome-to-adafruit-io)

---

⭐ Bu projeyi beğendiyseniz yıldızlamayı unutmayın!
