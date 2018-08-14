# tensorflow-android
本文档将帮助你在 win10_x64位 上建立 AS 工程，在 Android 5.0 之后的手机上生成 TF Classify, TF Detect, TF Speech, TF Stylize 四个安卓应用  
## 1 准备
翻墙工具准备好（或者用 ipv6），全程开，下载安装好最新的 Android Studio（需要翻墙）  
根据这个 https://www.cnblogs.com/xiadewang/p/7820377.html 或者类似的教程走一遍  
可能有些步骤会不一样，自行解决，安装过程会下载安装好 SDK  

下载 tensorflow 的 zip 压缩包：https://github.com/tensorflow/tensorflow  
解压到最好是全英文路径的位置，这里使用 1.5 版本  
## 2 Android Studio 打开工程
用 Android Studio 打开工程目录 "path\to\TF\tensorflow-1.5.0\tensorflow\examples\android"   
打开工程后会提示相应 gradle 设置并建立工程  
gradle 的压缩包会下载到 "C:\Users\用户名\.gradle\wrapper\dists\gradle-4.1-all\bzyivzo6n839fup2jbap0tjew"  
最后那个乱序的文件夹名称可能会不同，下载过程即使翻墙了也会很慢，可以自己先浏览器搜索 gradle-4.1-all 下好放到目录中，再打开工程，不知道这样上面那个目录还会不会存在  

修改 build.gradle 和 download-models.gradle 文件中所有的jcenter()为  
```Bash
jcenter {
   url 'http://jcenter.bintray.com'
}
```
```Bash
repositories {
    //jcenter()
    jcenter {
       url 'http://jcenter.bintray.com'
    }
    maven {
       url 'https://maven.google.com'
    }
    google()
}
```
```Bash
android {
    compileSdkVersion 28
    buildToolsVersion '28.0.2'
    ...
}
# 对应 AS 3.1.2
```
## 3 自己编译 libtensorflow_demo.so
同样在 build.gradle中，修改 nativeBuildSystem：
```Bash
def nativeBuildSystem = 'cmake'
```
修改 "path\to\TF\tensorflow-1.5.0\tensorflow\examples\android\jni" 目录下 CmakeLists.txt 中的 TF_SRC_ROOT：
```Bash
get_filename_component(TF_SRC_ROOT ${CMAKE_SOURCE_DIR}/include ABSOLUTE)
```
在 jni 目录下新建 include 文件夹，把编译 object_tracking 所需要的 .h 头文件复制到此目录下，包括 tensorflow/core 和 tensorflow/examples 子目录的头文件  
步骤 2 和 3 建立工程期间会提示下载 NDK 和 cmake，在 Android Studio 右上角的 SDK Manager 中找到并勾选  
## 4 下载模型
```Bash
def models = ['inception5h.zip',
              'object_detection/ssd_mobilenet_v1_android_export.zip',
              'stylize_v1.zip',
              'speech_commands_conv_actions.zip']
```
用浏览器下载，下载地址  
https://storage.googleapis.com/download.tensorflow.org/models/inception5h.zip   
https://storage.googleapis.com/download.tensorflow.org/models/object_detection/ssd_mobilenet_v1_android_export.zip  
https://storage.googleapis.com/download.tensorflow.org/models/stylize_v1.zip  
https://storage.googleapis.com/download.tensorflow.org/models/speech_commands_conv_actions.zip  
放到 "path\to\TF\tensorflow-1.5.0\tensorflow\examples\android\gradleBuild\downloads" 下面，继续建立工程  
可能会报如下警告，不用管  
```Bash
Configuration 'compile' is obsolete and has been replaced with 'implementation' and 'api'.
It will be removed at the end of 2018. For more information see: http://d.android.com/r/tools/update-dependency-configurations.html
```
## 生成 APK
手机连接电脑，并设置成 USB 调试  
AS 上 Build APK(s)  
感谢前人的工作  
