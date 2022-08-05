## **Problemin Tanımı**

Labirent problemi, bir çok kişinin aşina olduğu bir problem türüdür. Labirentin belirli noktaları başlangıç ve bitiş olarak belirlenmiştir. Problemde başlangıç noktasından başlayarak bitiş noktasının bulunması istenmektedir. Bu problemin çözümü için farklı algoritmalar kullanılabilir. Ödev kapsamında problemin çözümü için DFS (depth-first search) algoritması kullanılmıştır.

## Problemin Modellenmesi

 Labirent, çözümümüzde “maze.txt” isimli bir metin belgesinde saklanmaktadır. Bu metin belgesinde labirentin formatlanması şu şekildedir.
 ![enter image description here](https://i.hizliresim.com/9y0ihkm.png)
 Virgülden önceki kısım satır, sonraki kısım sütun numarasını göstermektedir. Başlangıç noktası “b”, çıkış noktası “c” ile ifade edilmektedir. Labirentin duvarları “+”, ”-“ ve “|” karakterleri ile ifade edilmektedir.

## Problemin Çözümü

 

## 1.Aşama

  Problemin çözümünde stack veri yapısı ve DFS algoritması kullanılmıştır. Labirent içinde bulunan elmalar rastgele bir şekilde boş noktalara yerleştirilmiştir. İlk aşamada metin belgesinden alınan labirent programda dinamik bir şekilde oluşturulmuş ve karakterlerden oluşan bir matris yoluyla tutulmuştur. Sonrasında bu matristen “visited” adlı int değerlerden oluşan bir matris oluşturulmuştur. Bu matriste; 0 : Daha önce gezilmemiş ve gidilebilir noktaları 1 : Duvar olduğu için gezilemeyecek noktaları 2 : Bitiş noktasını 3 : Elmaların olduğu noktaları 4 : Daha önce bir kez geçilen noktaları 5: Daha önce iki kez geçilen noktaları (çıkmaz noktadan dönerken) göstermektedir.
 

## 2.Aşama

 Labirent matrislerinin oluşturulmasından sonra labirenti çözmek üzere DFS fonksiyonu kullanılmıştır. DFS fonksiyonunda left, right, top ve bottom fonksiyonları kullanılmıştır. Bu fonksiyonlar bulunulan konumun sol, sağ, üst ve alt komşularının “visited” matrisindeki değerini kontrol eder. Bu noktalardan gidilebilecek noktalar tespit edilir ve push fonksiyonu ile yığına gönderilir. Bu kısımda ayrıca puan da kontrol edilir. Bulunulan konumda elma varsa 10 puan artırılır. Bulunulan konumdan hiçbir yere gidilemiyorsa (çıkmaz nokta) 5 puan düşürülür. Fonksiyonun son kısmı rekörsif kısmıdır. Yığına en son pushlanan noktanın koordinatları bir sonraki fonksiyon çağrısının parametreleri olacak şekilde belirlenir ve fonksiyon çağırılır. Fonksiyon çağrılmadan önce gidilen nokta pop fonksiyonu ile yığından çıkarılır. Örnek olarak bir noktadan iki farklı noktaya gidilebileceği durumlarda yığına en son pushlanan noktadan rekörsif çağrılar sayesinde gidilebilecek en son noktaya gidilir. Eğer bir çıkmaz noktaya girildiyse yığındaki son değer olan noktaya dönülür ve buradan gidilebilecek en son noktaya doğru devam edilir. Bir noktadan gidilebilecek tüm noktaların yığında tutulması bu noktanın bir kayıt noktası işlevi görmesini sağlar.
