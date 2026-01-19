#include "qrcodegen.hpp"
#include "wirehair.h"

#include <print>
#include <vector>
#include <iostream>
#include <sstream>
#include <random>

#include <QApplication>
#include <QMainWindow>
#include <QSvgWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QByteArray>
#include <QTimer>
#include <QLabel>

using std::vector, std::cout, std::endl;
using namespace qrcodegen;


static std::string toSvgString(const QrCode &qr, int border)
{
    if (border < 0)
        throw std::domain_error("Border must be non-negative");
    if (border > INT_MAX / 2 || border * 2 > INT_MAX - qr.getSize())
        throw std::overflow_error("Border too large");

    std::ostringstream sb;
    sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
    sb << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
    sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
    sb << "\t<path d=\"";
    for (int y = 0; y < qr.getSize(); y++)
    {
        for (int x = 0; x < qr.getSize(); x++)
        {
            if (qr.getModule(x, y))
            {
                if (x != 0 || y != 0)
                    sb << " ";
                sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
            }
        }
    }
    sb << "\" fill=\"#000000\"/>\n";
    sb << "</svg>\n";
    return sb.str();
}

class QRCodeWindow : public QMainWindow {
    Q_OBJECT
public:
    QRCodeWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("QR Code Viewer");
        resize(1000, 1100);
        
        centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        layout = new QVBoxLayout(centralWidget);
        
        svgWidget = new QSvgWidget(centralWidget);
        layout->addWidget(svgWidget);
        
        statusLabel = new QLabel(centralWidget);
        layout->addWidget(statusLabel);

        layout->setStretch(0, 10);  // svgWidget占10份
        layout->setStretch(1, 1);   // statusLabel占1份
        
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &QRCodeWindow::updateQRCode);
    }
    
    void startDisplay(const vector<uint8_t>& _message, int _packetSize) {
        this->message = _message;
        this->packetSize = _packetSize;
        currentBlockId = 0;
        
        encoder = wirehair_encoder_create(nullptr, &message[0], message.size(), packetSize);
        if (!encoder) {
            statusLabel->setText("Failed to create encoder");
            return;
        }
        
        timer->start(30); // 刷新率
    }
    
private slots:
    void updateQRCode() {
        if (!encoder) return;
        
        vector<uint8_t> block(packetSize);
        uint32_t writeLen = 0;
        
        WirehairResult encodeResult = wirehair_encode(
            encoder,
            currentBlockId,
            &block[0],
            packetSize,
            &writeLen
        );
        
        if (encodeResult != Wirehair_Success) {
            statusLabel->setText(QString("Encode failed at block %1").arg(currentBlockId));
            timer->stop();
            return;
        }

        // 创建二维码
        QrCode qr = QrCode::encodeBinary(block, QrCode::Ecc::LOW);
        
        // 转换为SVG
        auto svg = toSvgString(qr, 10);
        
        // 更新显示
        QByteArray svgData(svg.c_str());
        svgWidget->load(svgData);
        
        // 更新状态
        statusLabel->setText(QString("Block ID: %1, Size: %2 bytes").arg(currentBlockId).arg(writeLen));
        
        currentBlockId++;
    }
    
private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QSvgWidget *svgWidget;
    QLabel *statusLabel;
    QTimer *timer;
    
    vector<uint8_t> message;
    int packetSize;
    unsigned currentBlockId;
    WirehairCodec encoder;
};

#include "qrcode_stream_sender.moc"

int main(int argc, char *argv[]) try
{
    const WirehairResult initResult = wirehair_init();

    if (initResult != Wirehair_Success)
    {
        cout << "!!! Wirehair initialization failed: " << initResult << endl;
        return -1;
    }
    //
    // if (!ReadmeExample())
    // {
    //     cout << "!!! Example usage failed" << endl;
    //     return -2;
    // }
    QApplication app(argc, argv);
    
    // 准备测试数据
    constexpr int kPacketSize = 1024; // 1KB
    constexpr int kMessageBytes = 5 * 1024 * 1024; // 5MB

    std::string str = R"(
Triton 旨在通过提供一种可以编译为高效的 CUDA 本地代码的高级抽象，使编写高性能 GPU 代码变得更加容易。在这篇文章中，我将深入探讨 Triton 的内部机制，并探索 Triton 程序如何在幕后编译为 CUDA 内核（具体来说是 CUBIN）Cuda Compilation在深入了解 triton 之前，了解使用 nvcc 的 cuda 编译过程是有用的。以下来自 NVIDIA 文档的图表展示了整个 cuda 编译为可执行代码的过程。
CUDA 编译器（nvcc）预处理输入程序以供设备编译。这包括处理如#include 和与设备代码相关的宏等指令。 预处理后的设备代码被编译成 CUDA 二进制文件（cubin）和/或 PTX（并行线程执行）中间代码。 PTX 是 CUDA 的低级虚拟机和汇编语言。它允许进行优化并且是架构无关的。 Cubin 是针对目标架构优化的 GPU 特定二进制代码。两者 cubin 和 PTX 都会被放入 fatbinary 中，fatbinary 包含针对不同 GPU 架构优化的多种代码版本。看一个简单的 cuda -> ptx 的例子。

作者：Arthur
链接：https://zhuanlan.zhihu.com/p/1900918897022046521
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
)";

    while (str.size() < kMessageBytes)
    {
        str += str;
    }

    vector<uint8_t> message(str.begin(), str.end());
    message.resize(kMessageBytes);
    
    // 创建并显示窗口
    QRCodeWindow window;
    window.show();
    
    // 开始显示二维码
    window.startDisplay(message, kPacketSize);
    
    return app.exec();
}
catch (std::exception &e)
{
    std::println(stderr, "Exception: {}", e.what());
    return -1;
}
