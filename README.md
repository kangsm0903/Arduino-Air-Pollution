# Arduino-Project-Air-Pollution
### 대기질 오염도 측정 및 알림 

* ##### 미세먼지 센서(GP2Y1014AU), 온습도 센서, 이산화탄소 및 TVOC센서(CCS811), CO-NH3-NO2센서(MICS-6814), 포름알데히드 센서(sen0231)
* ##### + 알림 창에 미세먼지 - 마스크 / 이산화탄소 - 열린 창문 이미지 추가
* ##### + 회로도 추가
* ##### + 측정값 반환 화면 추가

* * *
* #### 회로도
<img src="https://user-images.githubusercontent.com/48651812/173087361-676d00ca-a149-4e81-b8cd-961ade45e749.png" width="600" height="500">

* * *

* #### MIT APP Inventor: 측정값 반환 화면 

<img src="https://user-images.githubusercontent.com/48651812/175314151-3d6a045c-f708-453f-8be6-afc5f850eb7c.jpg" width="250" height="500">&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;<img src="https://user-images.githubusercontent.com/48651812/172056756-c3c087d0-a83a-4a52-a8bc-524aae8dc393.jpg" width="250" height="500">

* * *

* #### MIT APP Inventor: 미세먼지 나쁨일 때 알림 화면
80ug/m3 이상 시 5초동안 50개의 미세먼지 농도를 누적합하여 평균 산출, 평균값이 80ug/m3 이상이면 알림 설정 

(매우 나쁨도 마찬가지)

<img src="https://user-images.githubusercontent.com/48651812/172400408-0418dca9-2e30-4331-a667-05dabe388ab8.jpg" width="250" height="500"> &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; <img src="https://user-images.githubusercontent.com/48651812/172400324-c983835c-93d7-4d33-b26d-2e1169b0533b.jpg" width="250" height="500">

* * *

* #### MIT APP Inventor: 이산화탄소 나쁨일 때 알림 화면
1000ppm 이상 시 50개의 이산화탄소 농도를 누적합하여 평균 산출, 평균값이 1000ppm 이상이면 알림 설정

<img src="https://user-images.githubusercontent.com/48651812/172400219-820a10fb-aab2-47ff-b367-a34c3a8ca87b.jpg" width="250" height="500"> &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; <img src="https://user-images.githubusercontent.com/48651812/172400020-685570ad-7707-4d8e-ad62-1a3bb8ba8fe9.jpg" width="250" height="500">



