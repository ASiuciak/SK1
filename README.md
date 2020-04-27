# SK1
Duże zadanie 1 z Sieci Komputerowych 2020 - program klienta HTTP

Klient po zinterpretowaniu argumentów wiersza poleceń łączy się ze wskazanym adresem i portem, wysyła do serwera HTTP żądanie podania wskazanej strony, odbiera odpowiedź od serwera, analizuje wynik i podaje raport.

Opis komunikacji
Techniczny opis formatu żądań i odpowiedzi HTTP znajduje się w dokumencie RFC7230. Klient ma połączyć się ze wskazanym adresem i portem, a następnie wysłać odpowiednie żądanie HTTP. Adres i port połączenia nie muszą się zgadzać z adresem i portem wskazanym w adresie testowanej strony. Żądanie HTTP ma zawierać odpowiednio umieszczone w swojej treści:

adres serwera, z którego będziemy ściągać zasób;
wskazanie zasobu, który ma zostać pobrany;
określone przez parametry w wierszu poleceń ciasteczka;
wskazanie, że po zakończeniu przesyłania zasobu połączenie ma zostać przerwane.
Jeśli odpowiedź serwera jest inna niż 200 OK (np. 202 Accepted) klient ma podać raport w postaci zawartości wiersza statusu uzyskanej odpowiedzi. Jeśli odpowiedź serwera jest 200 OK, raport ma składać się z dwóch części: zestawienia ciasteczek oraz rzeczywistej długości przesyłanego zasobu. Techniczny opis formatu pola nagłówkowego Set-Cookie znajduje się w dokumencie RFC2109. Należy tutaj pamiętać, że jedna odpowiedź HTTP może zawierać wiele pól Set-Cookie. Należy przyjąć, że jedno pole nagłówkowe Set-Cookie ustawia jedno ciasteczko. Jeśli w jednym polu ustawiane jest wiele ciasteczek należy ciasteczka poza pierwszym pominąć. Jeśli implementacja przyjmuje ograniczenia na liczbę przyjmowanych ciasteczek i ich długość, to ograniczenia te powinny zostać dobrane zgodnie z założeniami przyjętymi w standardach HTTP dla rozwiązań ogólnego przeznaczenia. Dodatkowo przy liczeniu długości przesyłanego zasobu należy uwzględnić możliwość, że zasób był wysłany w częściach (kodowanie przesyłowe chunked).
