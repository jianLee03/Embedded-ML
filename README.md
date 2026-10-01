# Embedded-ML

## class

전공 진행 실습, 기록 시작(2026.09.29-)

* 보드 : STM32 Nucleo-64 F103 R
* Tool : 아두이노 IDE, STM32 큐브 프로그래머

### A0\_Light\_

A0에 들어오는 전압을 0.1초마다 측정

### D7\_Light\_Dark\_Test

D7 디지털 입력값으로 LIGHT/DARK 판별, 시리얼 모니터 출력

### D9\_Digital\_Toggle\_Test

D9 핀에서 HIGH/LOW 0.5초 간격 반복 출력

### D10\_PWM\_128\_Test

D10 핀에 약 50% 듀티비의 PWM 신호 지속적으로 출력

### D10\_PWM\_Duty\_Test

D10 핀의 PWM 듀티비를 100% → 75% → 50% → 25%로 변화

### Serial\_Count\_Test

count 값을 증가시켜 0.5초마다 시리얼 모니터 출력

### Switch_Sensor_Buzzer_Control
D4 스위치로 시스템을 ON/OFF, ON 상태에서 A0 센서값이 기준값 350을 넘으면 D8 부저를 작동
