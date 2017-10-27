#include "Com.h"
extern UART_HandleTypeDef UartHandle;
static const uint8_t auchCRCHi[] = {
0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,0x80,
0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x00,0xC1,
0x81,0x40,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x01,
0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,
0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,
0x41,0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,
0x80,0x41,0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,0x01,
0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,
0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,
0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,0x80,0x41,0x00,0xC1,
0x81,0x40,0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x00,
0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,0x80,0x41,
0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,
0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,
0x80,0x41,0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,0x01,
0xC0,0x80,0x41,0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,
0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,
0x40,0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x01,0xC0,
0x80,0x41,0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x01,
0xC0,0x80,0x41,0x00,0xC1,0x81,0x40,0x00,0xC1,0x81,0x40,
0x01,0xC0,0x80,0x41,0x01,0xC0,0x80,0x41,0x00,0xC1,0x81,
0x40,0x00,0xC1,0x81,0x40,0x01,0xC0,0x80,0x41,0x00,0xC1,
0x81,0x40,0x01,0xC0,0x80,0x41,0x01,0xC0,0x80,0x41,0x00,
0xC1,0x81,0x40} ;
static const uint8_t auchCRCLo[] = {
0x00,0xC0,0xC1,0x01,0xC3,0x03,0x02,0xC2,0xC6,0x06,0x07,
0xC7,0x05,0xC5,0xC4,0x04,0xCC,0x0C,0x0D,0xCD,0x0F,0xCF,
0xCE,0x0E,0x0A,0xCA,0xCB,0x0B,0xC9,0x09,0x08,0xC8,0xD8,
0x18,0x19,0xD9,0x1B,0xDB,0xDA,0x1A,0x1E,0xDE,0xDF,0x1F,
0xDD,0x1D,0x1C,0xDC,0x14,0xD4,0xD5,0x15,0xD7,0x17,0x16,
0xD6,0xD2,0x12,0x13,0xD3,0x11,0xD1,0xD0,0x10,0xF0,0x30,
0x31,0xF1,0x33,0xF3,0xF2,0x32,0x36,0xF6,0xF7,0x37,0xF5,
0x35,0x34,0xF4,0x3C,0xFC,0xFD,0x3D,0xFF,0x3F,0x3E,0xFE,
0xFA,0x3A,0x3B,0xFB,0x39,0xF9,0xF8,0x38,0x28,0xE8,0xE9,
0x29,0xEB,0x2B,0x2A,0xEA,0xEE,0x2E,0x2F,0xEF,0x2D,0xED,
0xEC,0x2C,0xE4,0x24,0x25,0xE5,0x27,0xE7,0xE6,0x26,0x22,
0xE2,0xE3,0x23,0xE1,0x21,0x20,0xE0,0xA0,0x60,0x61,0xA1,
0x63,0xA3,0xA2,0x62,0x66,0xA6,0xA7,0x67,0xA5,0x65,0x64,
0xA4,0x6C,0xAC,0xAD,0x6D,0xAF,0x6F,0x6E,0xAE,0xAA,0x6A,
0x6B,0xAB,0x69,0xA9,0xA8,0x68,0x78,0xB8,0xB9,0x79,0xBB,
0x7B,0x7A,0xBA,0xBE,0x7E,0x7F,0xBF,0x7D,0xBD,0xBC,0x7C,
0xB4,0x74,0x75,0xB5,0x77,0xB7,0xB6,0x76,0x72,0xB2,0xB3,
0x73,0xB1,0x71,0x70,0xB0,0x50,0x90,0x91,0x51,0x93,0x53,
0x52,0x92,0x96,0x56,0x57,0x97,0x55,0x95,0x94,0x54,0x9C,
0x5C,0x5D,0x9D,0x5F,0x9F,0x9E,0x5E,0x5A,0x9A,0x9B,0x5B,
0x99,0x59,0x58,0x98,0x88,0x48,0x49,0x89,0x4B,0x8B,0x8A,
0x4A,0x4E,0x8E,0x8F,0x4F,0x8D,0x4D,0x4C,0x8C,0x44,0x84,
0x85,0x45,0x87,0x47,0x46,0x86,0x82,0x42,0x43,0x83,0x41,
0x81,0x80,0x40};
uint8_t Data_Recv[2099]={0,};
uint8_t Data_Tran[30]={0,};
uint8_t Device_ID[]="10MFFFFFFFFFFFFFF";
/*要接受的数据空间和要发送的数据空间*/
/*通信状态量*/
Com_Status Status;
HAL_StatusTypeDef Status1;
uint8_t Rev_Status=0;
/*报文内容长度及CRC校验数据映射量*/
uint32_t packetlength=0;
uint16_t CRC_Value=0;
uint16_t filepacketNo_Map_start=0;/////启动包映射
uint16_t filepacketNo_Map_process=0;////过程包映射
uint16_t filepacketNo_Map_end=0;////结束包映射
uint16_t Onepacketlength_Map=0;
uint32_t filelength_Map;
uint16_t SubpacketNo_Map=0;
uint32_t A_Map=0;
uint32_t B_Map=0;
uint32_t C_Map=0;
uint32_t D_Map=0;
uint8_t  filename_Map[20];
/*MD5校验相关变量*/
uint32_t A;
uint32_t B;
uint32_t C;
uint32_t D;
uint32_t a;
uint32_t b;
uint32_t c;
uint32_t d;
uint32_t M[16]={0,};
uint32_t flength[2];
__IO uint32_t N=0;
__IO uint32_t R=0;
/*FLASH刷写地址*/
__IO uint32_t flashdestination=Write_Startaddress ;
/*升级标志*/
__IO uint32_t Upgrade_flag=Upgrade_Fail;
uint8_t Start=0;
uint32_t Error=0;
Com_Status OnePacket_Rec(){
  Uart_init();
  Status1=Uart_Receive_IT(Data_Recv ,24);
  if(Status1==HAL_TIMEOUT)return Com_Timeout;
  else{
      packetlength=Data_Recv[3];
      packetlength<<=8;
      packetlength+=Data_Recv[2];
      Status1=Uart_Receive_IT(Data_Recv+24,packetlength+3);
      if(Status1==HAL_TIMEOUT)return Com_Timeout;
      else{
            Data_Map(Data_Recv+24+packetlength,1);/////对CRC校验码进行映射
            if(Data_Recv[1]!=0x5A||Data_Recv[0]!=0xA5)return Com_Error;
            else if(Data_Recv[21]!=frametype_host)return Com_Error;
            else if(Data_Recv[24+packetlength+2]!=End_Value )return Com_Error;
            else if(Com_String(Data_Recv+4,Device_ID,Device_CodeNumber)==0)return Com_Error;
            else if(Data_Recv[22]==packettype_start){Data_Map(Data_Recv+24,packettype_start);return Com_Start;}
            else if(Data_Recv[22]==packettype_process){Data_Map(Data_Recv+24,packettype_process);return Com_OK_this;}
            else if(Data_Recv[22]==packettype_end){Data_Map(Data_Recv+24,packettype_end);return Com_Exit;}
            else return  Com_Error;
        }
      
  }
}
uint8_t  Communication(void){
    Status=OnePacket_Rec();
    switch(Status){
      case Com_Start:{
          if(CRC_Value==RTU_CRC(Data_Recv+2,66)){
            if(filelength_Map>Maxfilelength)Rev_Status=0x02;
            else if(filelength_Map<1024)Rev_Status=0x03;//////此处待定
            else if(filepacketNo_Map_start*Onepacketlength_Map<=filelength_Map)Rev_Status=0x04;
            else if(Onepacketlength_Map>2048)Rev_Status=0x05;
            else if(Onepacketlength_Map<128)Rev_Status=0x06;
            else Rev_Status=0x01;      
          }
          else Rev_Status=0x07;
          OnePacket_Tra(frametype_ack,packettype_start,Rev_Status,packettype_start); 
          HAL_UART_DeInit(&UartHandle);
          if(Rev_Status==0x01){
            Start++;
            if((Upgrade_flag==Upgrade_OK||Upgrade_flag==Upgrade_Fail)&&Start<=1){////无论升级成功或者失败，均清除文件保存区
              Flash_Erase(Write_Startaddress,Write_Endaddress);
              flashdestination=Write_Startaddress;
            }
          }
          break;
      }
      case Com_OK_this:{
        if(CRC_Value==RTU_CRC(Data_Recv+2,packetlength+22)){
            if(Com_String(filename_Map,Data_Recv+24,20)==0)Rev_Status=0x00;////////文件名不符，升级失败
            else if(filepacketNo_Map_process!=filepacketNo_Map_start)Rev_Status=0x00;/////总包数不符，升级失败
            else{
              if(SubpacketNo_Map<=filepacketNo_Map_process){
                Rev_Status=0xFF; 
              }
              else Rev_Status=0x00;
            }
        }
        else Rev_Status=0x00;
       
        if(Rev_Status==0xFF){
          if (FLASH_Write_8(flashdestination, Data_Recv+48, packetlength-24) == FLASH_Program_OK){
                flashdestination += (packetlength-24);
                SubpacketNo_Map++;
          }
          else Rev_Status=0x00;
          
        }
        if(Rev_Status==0x00){Upgrade_flag=Upgrade_Onepacket_Error;Error++;} 
        if(Error>=10){Error=0;Rev_Status=0xBB;Upgrade_flag=Upgrade_Fail;}
        OnePacket_Tra(frametype_ack,packettype_process,Rev_Status,packettype_process);
        break;
      }
      case Com_Exit:{
        if(CRC_Value==RTU_CRC(Data_Recv+2,packetlength+22)){
          MD5_init();
          MD5_Cal();
          if(A==A_Map&&B==B_Map&&C==C_Map&&D==D_Map){///表示通过MD5校验
            Rev_Status=0xFF;
          }
          else Rev_Status=0x00;
        }
        else Rev_Status=0x00;
        OnePacket_Tra(frametype_ack,packettype_end ,Rev_Status,packettype_end);
        if(Rev_Status==0xFF){
          Upgrade_flag=Upgrade_OK;
          Flash_Erase(Flag_Start_address ,Flag_End_address );
          HAL_FLASH_Program(TYPEPROGRAM_WORD, Upgrade_flag_address, Upgrade_flag);
          HAL_FLASH_Program(TYPEPROGRAM_WORD, filelength_address, filelength_Map);
          //HAL_UART_DeInit(&UartHandle);
          Start=0;
          return 1;
        }
        else if(Rev_Status==0x00){
            Upgrade_flag=Upgrade_Fail;
            HAL_FLASH_Program(TYPEPROGRAM_WORD, Upgrade_flag_address, Upgrade_flag);
            Start=0;
        }
       
        break;
      }
      case Com_Timeout:{/////需要处理超时和数据错误的情况的情况
        break;
      }
      case Com_Error:{
          OnePacket_Tra(frametype_ack,packettype_process ,0x00,packettype_process);
      }
      
    }
    return 0;
}
void OnePacket_Tra(uint8_t In1,uint32_t In2,uint8_t In3,uint8_t type){//第一个参数是frametype,第二个参数是packettype,第三个参数是Rev_Status，第四个参数是应答数据包类型
  uint16_t CRC_Value;
  uint32_t i;
  if(type==0xC7){
    sendByte(Sync0);
    sendByte(Sync1);

    sendByte(packetlength0_start);
    sendByte(packetlength1_start);
    Data_Tran[2]=packetlength0_start;
    Data_Tran[3]=packetlength1_start;
  
    for(i=0;i<Device_CodeNumber;i++){
      sendByte(*(Data_Recv+4+i));
    }
    Cpy_String(Data_Tran+4,Data_Recv+4,Device_CodeNumber);

    sendByte(In1);
    sendByte(In2);
    sendByte(Data_Recv[23]);   
    sendByte(In3); 
    Data_Tran[21]=In1;
    Data_Tran[22]=In2;
    Data_Tran[23]=Data_Recv[23];
    Data_Tran[24]=In3;
  
    sendByte((uint8_t)(SubpacketNo_Map));
    sendByte((uint8_t)(SubpacketNo_Map>>8));
    Data_Tran[25]=(uint8_t)SubpacketNo_Map;
    Data_Tran[26]=(uint8_t)(SubpacketNo_Map>>8);
 
    CRC_Value=RTU_CRC(Data_Tran+2,25);
  
    sendByte((uint8_t)CRC_Value);
    sendByte((uint8_t)(CRC_Value>>8));
    sendByte(End_Value);

  }

  else if(type==0xC8||0xC9){
    sendByte(Sync0);
  sendByte(Sync1);

  sendByte(packetlength0);
  sendByte(packetlength1);
  Data_Tran[2]=packetlength0;
  Data_Tran[3]=packetlength1;
  
  for(i=0;i<Device_CodeNumber;i++){
    sendByte(*(Data_Recv+4+i));
  }
  Cpy_String(Data_Tran+4,Data_Recv+4,Device_CodeNumber);

  sendByte(In1);
  sendByte(In2);
  sendByte(Data_Recv[23]);   
  sendByte(In3); 
  Data_Tran[21]=In1;
  Data_Tran[22]=In2;
  Data_Tran[23]=Data_Recv[23];
  Data_Tran[24]=In3;
  
  CRC_Value=RTU_CRC(Data_Tran+2,23);
  
  sendByte((uint8_t)CRC_Value);
  sendByte((uint8_t)(CRC_Value>>8));
  sendByte(End_Value);
  }
}

void MD5_Loop(void){
        a=A,b=B,c=C,d=D;
        FF(a, b, c, d, M[0], 7, 0xd76aa478);
	FF(d, a, b, c, M[1], 12, 0xe8c7b756);
	FF(c, d, a, b, M[2], 17, 0x242070db);
	FF(b, c, d, a, M[3], 22, 0xc1bdceee);
	FF(a, b, c, d, M[4], 7, 0xf57c0faf);
	FF(d, a, b, c, M[5], 12, 0x4787c62a);
	FF(c, d, a, b, M[6], 17, 0xa8304613);
	FF(b, c, d, a, M[7], 22, 0xfd469501);
	FF(a, b, c, d, M[8], 7, 0x698098d8);
	FF(d, a, b, c, M[9], 12, 0x8b44f7af);
	FF(c, d, a, b, M[10], 17, 0xffff5bb1);
	FF(b, c, d, a, M[11], 22, 0x895cd7be);
	FF(a, b, c, d, M[12], 7, 0x6b901122);
	FF(d, a, b, c, M[13], 12, 0xfd987193);
	FF(c, d, a, b, M[14], 17, 0xa679438e);
	FF(b, c, d, a, M[15], 22, 0x49b40821);

	GG(a, b, c, d, M[1], 5, 0xf61e2562);
	GG(d, a, b, c, M[6], 9, 0xc040b340);
	GG(c, d, a, b, M[11], 14, 0x265e5a51);
	GG(b, c, d, a, M[0], 20, 0xe9b6c7aa);
	GG(a, b, c, d, M[5], 5, 0xd62f105d);
	GG(d, a, b, c, M[10], 9, 0x02441453);
	GG(c, d, a, b, M[15], 14, 0xd8a1e681);
	GG(b, c, d, a, M[4], 20, 0xe7d3fbc8);
	GG(a, b, c, d, M[9], 5, 0x21e1cde6);
	GG(d, a, b, c, M[14], 9, 0xc33707d6);
	GG(c, d, a, b, M[3], 14, 0xf4d50d87);
	GG(b, c, d, a, M[8], 20, 0x455a14ed);
	GG(a, b, c, d, M[13], 5, 0xa9e3e905);
	GG(d, a, b, c, M[2], 9, 0xfcefa3f8);
	GG(c, d, a, b, M[7], 14, 0x676f02d9);
	GG(b, c, d, a, M[12], 20, 0x8d2a4c8a);

	HH(a, b, c, d, M[5], 4, 0xfffa3942);
	HH(d, a, b, c, M[8], 11, 0x8771f681);
	HH(c, d, a, b, M[11], 16, 0x6d9d6122);
	HH(b, c, d, a, M[14], 23, 0xfde5380c);
	HH(a, b, c, d, M[1], 4, 0xa4beea44);
	HH(d, a, b, c, M[4], 11, 0x4bdecfa9);
	HH(c, d, a, b, M[7], 16, 0xf6bb4b60);
	HH(b, c, d, a, M[10], 23, 0xbebfbc70);
	HH(a, b, c, d, M[13], 4, 0x289b7ec6);
	HH(d, a, b, c, M[0], 11, 0xeaa127fa);
	HH(c, d, a, b, M[3], 16, 0xd4ef3085);
	HH(b, c, d, a, M[6], 23, 0x04881d05);
	HH(a, b, c, d, M[9], 4, 0xd9d4d039);
	HH(d, a, b, c, M[12], 11, 0xe6db99e5);
	HH(c, d, a, b, M[15], 16, 0x1fa27cf8);
	HH(b, c, d, a, M[2], 23, 0xc4ac5665);

	II(a, b, c, d, M[0], 6, 0xf4292244);
	II(d, a, b, c, M[7], 10, 0x432aff97);
	II(c, d, a, b, M[14], 15, 0xab9423a7);
	II(b, c, d, a, M[5], 21, 0xfc93a039);
	II(a, b, c, d, M[12], 6, 0x655b59c3);
	II(d, a, b, c, M[3], 10, 0x8f0ccc92);
	II(c, d, a, b, M[10], 15, 0xffeff47d);
	II(b, c, d, a, M[1], 21, 0x85845dd1);
	II(a, b, c, d, M[8], 6, 0x6fa87e4f);
	II(d, a, b, c, M[15], 10, 0xfe2ce6e0);
	II(c, d, a, b, M[6], 15, 0xa3014314);
	II(b, c, d, a, M[13], 21, 0x4e0811a1);
	II(a, b, c, d, M[4], 6, 0xf7537e82);
	II(d, a, b, c, M[11], 10, 0xbd3af235);
	II(c, d, a, b, M[2], 15, 0x2ad7d2bb);
	II(b, c, d, a, M[9], 21, 0xeb86d391);
        
        A += a;
        B += b;
        C += c;
        D += d;
}
void MD5_init(void){
    A = 0x67452301;
    B = 0xefcdab89;
    C = 0x98badcfe;
    D = 0x10325476;
}
void MD5_Cal(void){
  uint32_t i,j;
  uint32_t address=Write_Startaddress;
  flength[1]=0;     ////文件大小的高位
  flength[0]=filelength_Map*8;/////文件大小的低位由于文件大小不会超过32位，此处做简化处理
  N=filelength_Map/64;
  R=filelength_Map%64;
  for(j=0;j<16;j++){
      M[j]=0;
  }
  for(j=0;j<16;j++){
       M[j]=*(__IO uint32_t*)(address);
       address+=4;
  }
  for(i=0;i<N;i++){
    MD5_Loop();
    for(j=0;j<16;j++){
      M[j]=0;
    }
    for(j=0;j<16;j++){
      M[j]=*(__IO uint32_t*)(address);
      address+=4;
    }
  }
  ((uint8_t*)M)[R]=128;
  for(j=R+1;j<64;j++){
    if(((char*)M)[j]==0xFF)((char*)M)[j]=0x00;
  }
  if(R>55){
    MD5_Loop();
    for(j=0;j<16;j++){
      M[j]=0;
    }
  }
  M[14]=flength[0];
  M[15]=flength[1];
  MD5_Loop();
  A=PP(A);
  B=PP(B);
  C=PP(C);
  D=PP(D);
}

void Cpy_String(uint8_t* Data1,uint8_t* Data2,uint32_t length){/////将Data2中de数据拷贝到Data1中
 uint32_t i;
 for(i=0;i<length;i++){
   Data1[i]=Data2[i];
 }
}
uint8_t Com_String(uint8_t* Data1,uint8_t* Data2,uint32_t length){
  uint32_t i;
  for(i=0;i<length;i++){
    if(Data1[i]==Data2[i])continue;
    else break;
  }
  if(i<length)return 0;//////两个字符串不等
  else return 1;
}
void Data_Map(uint8_t* Data,uint8_t type){//////此函数用于将受到的报文中以8位数组形式存在的数据转化为16位或者32位数据
    uint32_t i;
   switch(type){
    case 1:
      CRC_Value=Data[1];
      CRC_Value<<=8;
      CRC_Value+=Data[0];
      break;
    case 0xC9:
      if(Data!=NULL){
         filepacketNo_Map_end=Data[21];
         filepacketNo_Map_end<<=8;
         filepacketNo_Map_end+=Data[20];
      }
      break;
      
      case 0xC8:
      if(Data!=NULL){
        filepacketNo_Map_process=Data[21];
        filepacketNo_Map_process<<=8;
        filepacketNo_Map_process+=Data[20];
        
        SubpacketNo_Map=Data[23];
        SubpacketNo_Map<<=8;
        SubpacketNo_Map+=Data[22];
      }
      break;
      
      case 0xC7:
        if(Data!=NULL){ 
          for(i=0;i<20;i++){
            filename_Map[i]=Data[i];/////保存文件名
          }
          
          filelength_Map=Com_4_Data(Data[23],Data[22],Data[21],Data[20]);
          
          A_Map=Com_4_Data(Data[24],Data[25],Data[26],Data[27]);
          B_Map=Com_4_Data(Data[28],Data[29],Data[30],Data[31]);
          C_Map=Com_4_Data(Data[32],Data[33],Data[34],Data[35]);
          D_Map=Com_4_Data(Data[36],Data[37],Data[38],Data[39]);
            
          filepacketNo_Map_start=Data[41];
          filepacketNo_Map_start<<=8;
          filepacketNo_Map_start+=Data[40];
          
          Onepacketlength_Map=Data[43];
          Onepacketlength_Map<<=8;
          Onepacketlength_Map+=Data[42];
        }
        
  }
  
        
  
}

uint32_t Com_4_Data(uint8_t in1,uint8_t in2,uint8_t in3,uint8_t in4){////高四位,。。。。。低四位
  uint32_t Data=0;
  uint32_t temp[4];
  temp[0]=in1;
  temp[1]=in2;
  temp[2]=in3;
  temp[3]=in4;
  temp[0]<<=24;
  temp[1]<<=16;
  temp[2]<<=8;
  Data=Data+temp[0]+temp[1]+temp[2]+temp[3];
  return Data;
}
uint16_t RTU_CRC( uint8_t * puchMsg,uint32_t usDataLen )
{
uint8_t uchCRCHi; // high byte of CRC initialized
uint8_t uchCRCLo; // low byte of CRC initialized
uint16_t uIndex; // will index into CRC lookup table
uchCRCHi = 0xFF;
uchCRCLo = 0xFF;
while ( usDataLen-- )
{
// calculate the CRC
uIndex = uchCRCHi^(uint8_t)( *puchMsg++ );
uchCRCHi = uchCRCLo^auchCRCHi[uIndex];
uchCRCLo = auchCRCLo[uIndex];
}
return ( uchCRCHi << 8 | uchCRCLo );
}
