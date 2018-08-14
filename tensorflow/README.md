# tensorflow-android
本文档将帮助你在 win10_x64位 上生成 TF Classify, TF Detect, TF Speech, TF Stylize 四个安卓应用  
## 1 准备
翻墙工具准备好（或者用 ipv6），下载安装好最新的 Android Studio（需要翻墙）  
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
## 3 自己编译 libtensorflow_demo.so
同样在 build.gradle中，修改 nativeBuildSystem：
```Bash
def nativeBuildSystem = 'cmake'
```
修改 "path\to\TF\tensorflow-1.5.0\tensorflow\examples\android\jni" 目录下 CmakeLists.txt 中的 TF_SRC_ROOT：
```Bash
get_filename_component(TF_SRC_ROOT ${CMAKE_SOURCE_DIR}/include ABSOLUTE)
```

