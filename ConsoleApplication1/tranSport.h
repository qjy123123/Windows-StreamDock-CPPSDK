#ifndef _TRANSPOT_
#define _TRANSPOT_
#undef UNICODE
#undef _UNICODE
#include <iostream>
#include "hidapi.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fstream>

class tranSport
{
private:
    hid_device *handle;
public:
    tranSport();
    /*
        @note:打开设备，使用设备路径打开
        @param path ：图片的路径
        @return 成功返回1，如果出错返回-1
    */
    int open(char *path);
     /*
        @note:获取设备的固件id
        @param lenth ：固件号长度（默认写512）
        @return 成功返回1，如果出错返回-1
    */
    unsigned char *getInputReport(int lenth);
     /*
        @note:读取设备的反馈信息 
        按键事件
        byte            内容        值         描述
        data[0]     回复的格式      0x41-A     
        data[1]     回复的格式      0x43-C  
        data[2]     回复的格式      0x4B-K  
        data[3-4]       预留
        data[5]     回复的格式      0x4F-O  
        data[6]     回复的格式      0x4B-K
        data[7-8]       预留
        data[9]     按键下标        0x01-0x0F
        data[10]     按键事件       0x00-0x01  0x00 按键抬起，0x01按键按下  
        
        应答消息  
        data[0]     回复的格式      0x41-A     
        data[1]     回复的格式      0x43-C  
        data[2]     回复的格式      0x4B-K  
        data[3-4]       预留
        data[5]     回复的格式      0x4F-O  
        data[6]     回复的格式      0x4B-K
        data[7-8]       预留
        data[9]     表示应答        0x00
        data[10-13]     预留  
        @param data ：用来接受反馈信息的unsigned char 数组
        @param lenth ：数组长度
        @return 成功返回1，如果出错返回-1
    */
    int read(unsigned char *data,unsigned long lenth);
    /*
        @note:向设备下发信息
        @param data:装有数据的unsigned char数组
        @param lenth：数组长度
        @return 成功返回1，如果出错返回-1
    */
    int write(unsigned char *data,unsigned long lenth);
    /*
        @note:将enumerate返回的设备信息列表销毁
        @param devs ：装有设备信息的链表
        @return 成功返回1，如果出错返回-1
    */
    void freeEnumerate(hid_device_info *devs);  
     /*
        @note:获取设备信息列表
        @param vid：设备vid
        @param pid：设备pid
        @return 成功返回1，如果出错返回-1
    */
    hid_device_info *enumerate(int vid, int pid);
    /*
        @note:设置设备屏幕亮度 0-100
        @param percent ：亮度 0-100
        @return 成功返回1，如果出错返回-1
    */
    int setBrightness(int percent);
    /*
        @note:设置设备屏幕的背景图
        @param buffer：放有BGR数据的unsigned char数组地址
        @param size：数组大小
        @return 成功返回1，如果出错返回-1
    */
    int setBackgroundImg(unsigned char *buffer,int size);
     /*
        @note:设置设备某个按键的图标
        @param path：图片路径
        @param key：按键标号
        @return 成功返回1，如果出错返回-1
    */
    int setKeyImg(std::string path,int key);
    /*
        @note:设置设备某个按键的图标
        @param buffer，装有图片信息的unsigned char 数组
        @param key：按键标号
        @param width： 图片长度
        @param height：图片高度
        @return 成功返回1，如果出错返回-1
    */
    int setKeyImgdata(unsigned char* buffer, int key, int width, int height);
    /*
        @note:清空某个按键的图标
        @param index ：按键标号（1-15）
        @return 成功返回1，如果出错返回-1
    */
    int keyClear(int index);
    /*
        @note:清空所有按键的图标
        @return 成功返回1，如果出错返回-1
    */
    int keyAllClear();
    /*
        @note:唤醒屏幕
        @return 成功返回1，如果出错返回-1
    */
    int wakeScreen();
    /*
        @note:在数据传输完成后可以用这个刷新显示
        @return 成功返回1，如果出错返回-1
    */
    int refresh();
     /*
        @note:断开连接
        @return 成功返回1，如果出错返回-1
    */
    int disconnected();
    /*
        @note:关闭设备
        @return 成功返回1，如果出错返回-1
    */
    void close();
};
#endif
