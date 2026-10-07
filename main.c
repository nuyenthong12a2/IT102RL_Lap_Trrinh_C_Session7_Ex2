#include <stdio.h>
#include <string.h>

#define MAX_CURRENT 30.0f
#define MAX_UNOCCUPIED 15
#define MAX_HOURS 744

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    struct SmartDevice device;
    struct EnergySensor sensor;
    float operatingHours;
    int c;

    printf("=== HE THONG QUAN LY NANG LUONG SMART HOME ===\n");
    printf("--- Nhap thong tin thiet bi ---\n");

    printf("Ma dinh danh thiet bi: ");
    if (scanf("%d", &device.deviceID) != 1) {
        printf("Loi: Ma thiet bi khong hop le!\n");
        return 1;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Ten thiet bi: ");
    if (fgets(device.deviceName, sizeof(device.deviceName), stdin) == NULL) {
        printf("Loi: Khong doc duoc ten thiet bi!\n");
        return 1;
    }
    device.deviceName[strcspn(device.deviceName, "\n")] = '\0';

    printf("Trang thai (1: Dang bat, 0: Da tat): ");
    if (scanf("%d", &device.status) != 1 || (device.status != 0 && device.status != 1)) {
        printf("Loi: Trang thai chi nhan gia tri 0 hoac 1!\n");
        return 1;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Cong suat dinh muc (kW): ");
    if (scanf("%f", &device.ratedPowerKW) != 1 || device.ratedPowerKW <= 0) {
        printf("Loi: Cong suat dinh muc phai lon hon 0!\n");
        return 1;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("--- Nhap du lieu cam bien ---\n");

    printf("Dien ap do duoc (V): ");
    if (scanf("%f", &sensor.voltageVolts) != 1) {
        printf("Loi: Du lieu dien ap khong hop le!\n");
        return 1;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Dong dien do duoc (A): ");
    if (scanf("%f", &sensor.currentAmperes) != 1) {
        printf("Loi: Du lieu dong dien khong hop le!\n");
        return 1;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Thoi gian vang nguoi (phut): ");
    if (scanf("%d", &sensor.unoccupancyMinutes) != 1) {
        printf("Loi: Thoi gian vang nguoi khong hop le!\n");
        return 1;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("So gio van hanh trong thang (gio): ");
    if (scanf("%f", &operatingHours) != 1) {
        printf("Loi: So gio van hanh khong hop le!\n");
        return 1;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    if (sensor.voltageVolts < 0 || sensor.currentAmperes < 0 || sensor.unoccupancyMinutes < 0) {
        printf("\n[LOI CAM BIEN] Du lieu cam bien am, nghi ngo loi phan cung. Huy thao tac xu ly!\n");
        return 1;
    }

    printf("\n--- KET QUA XU LY AN TOAN & TIET KIEM NANG LUONG ---\n");
    printf("Thiet bi: %s (ID: %d)\n", device.deviceName, device.deviceID);

    if (sensor.currentAmperes > MAX_CURRENT) {
        device.status = 0;
        printf("[CANH BAO] Dong dien %.1f A vuot nguong %.1f A! NGAT KHAN CAP, nguy co chay no!\n", sensor.currentAmperes, MAX_CURRENT);
    }

    if (device.status == 1 && sensor.unoccupancyMinutes >= MAX_UNOCCUPIED) {
        device.status = 0;
        printf("[TIET KIEM] Phong trong %d phut (>= %d phut). Tu dong tat thiet bi!\n", sensor.unoccupancyMinutes, MAX_UNOCCUPIED);
    }

    printf("Trang thai thiet bi sau xu ly: %s\n", device.status == 1 ? "DANG BAT" : "DA TAT");

    printf("\n--- TINH DIEN NANG & TIEN DIEN EVN ---\n");
    if (operatingHours <= 0 || operatingHours > MAX_HOURS) {
        printf("[LOI] So gio van hanh phai lon hon 0 va khong vuot qua %d gio. Tu choi tinh hoa don!\n", MAX_HOURS);
        return 1;
    }

    float kwh = device.ratedPowerKW * operatingHours;
    double tienDien;

    if (kwh <= 50) {
        tienDien = kwh * 1806;
    } else if (kwh <= 100) {
        tienDien = 50 * 1806 + (kwh - 50) * 1866;
    } else if (kwh <= 200) {
        tienDien = 50 * 1806 + 50 * 1866 + (kwh - 100) * 2167;
    } else {
        tienDien = 50 * 1806 + 50 * 1866 + 100 * 2167 + (kwh - 200) * 2729;
    }

    printf("Dien nang tieu thu: %.2f kWh\n", kwh);
    printf("Tien dien phai tra (chua VAT): %.0f VND\n", tienDien);

    return 0;
}