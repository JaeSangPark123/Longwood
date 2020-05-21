#include<stdio.h>
#include <math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

double sigmoid(double x);

float dsigmoid(float x);
int main(int argc,char* argv[]){
	FILE* fp;//train image label
	FILE* fp1;//train image pixel
	FILE* fp2;//test image label
	FILE* fp3;//test image pixel
	char trainlabel_idx1[100];
	char trainimage_idx3[100];
	char testlabel_idx1[100];
	char testimage_idx3[100];
	unsigned char* temp;
	unsigned char* trainlabel;
	unsigned char** trainpixel;
	unsigned char* testlabel;
	unsigned char** testpixel;
	int i=0;
	int j=0;
	int k=0;
	int index=0;
	double neuron[785]={0};
	double weight[785][10]={0};
	double simple[785]={0};
	double out=0;
	double outlayer[10]={0};
	int epoch=0;
	double learningrate=0.0;
	unsigned char* label;
	label = (unsigned char*)malloc(sizeof(unsigned char));
	trainlabel = (unsigned char*)malloc(sizeof(unsigned char)*60000);
	trainpixel = (unsigned char**)malloc(sizeof(unsigned char*)*60000);
	testlabel = (unsigned char*)malloc(sizeof(unsigned char)*10000);
	testpixel = (unsigned char**)malloc(sizeof(unsigned char*)*10000);
	for(i=0;i<60000;i++){
		trainpixel[i] = (unsigned char*)malloc(sizeof(unsigned char)*784);
	}
	for(i=0;i<10000;i++){
		testpixel[i] = (unsigned char*)malloc(sizeof(unsigned char)*784);
	}
	if(argc==1){

		printf("./proj2 <epoch> <learningrate> <mnist/train-labels-idx1-ubyte> <mnist/train-imagefile-idx3-ubyte> <mnist/t10k-labels-idx1-ubyte> mnist/t10k-images-idx3-ubyte>\n");
		return 0;
	}
	if(argc != 7){
		printf("Invalid input\n");
		printf("./proj2 <epoch> <learningrate> <mnist/train-labels-idx1-ubyte> <mnist/train-imagefile-idx3-ubyte> <mnist/t10k-labels-idx1-ubyte> mnist/t10k-images-idx3-ubyte>\n");
		return 0;
	}
	epoch = atoi(argv[1]);
	learningrate = atof(argv[2]);
	temp = (unsigned char*)malloc(sizeof(unsigned char));
	while(1){
		fp = fopen(argv[3],"rb");//train label
		if(fp==NULL){
			printf("file open error! 1\n");
			printf("try again!\n");
			printf("train-labels-idx1-ubyte\n");
			printf("Insert image file: ");
			scanf("%s",argv[3]);
		}
		else{
			strcpy(trainlabel_idx1,argv[4]);
			break;
		}
	}
	while(1){
		fp1 = fopen(argv[4],"rb");//train pixel
		if(fp1==NULL){
			printf("file open error! 2\n");
			printf("try again\n");
			printf("train-images-idx3-ubyte\n");
			printf("Insert image file: ");
			scanf("%s",argv[4]);
		}
		else{
			strcpy(trainimage_idx3,argv[4]);
			break;
		}
	}
	while(1){
		fp2 = fopen(argv[5],"rb");//train pixel
		if(fp1==NULL){
			printf("file open error! 2\n");
			printf("try again\n");
			printf("t10k-labels-idx1-ubyte\n");
			printf("Insert label file: ");
			scanf("%s",argv[5]);
		}
		else{
			strcpy(testlabel_idx1,argv[5]);
			break;
		}
	}
	while(1){
		fp3 = fopen(argv[6],"rb");//train pixel
		if(fp1==NULL){
			printf("file open error! 2\n");
			printf("try again\n");
			printf("t10k-images-idx3-ubyte\n");
			printf("Insert image file: ");
			scanf("%s",argv[6]);
		}
		else{
			strcpy(testimage_idx3,argv[6]);
			break;
		}
	}
	fseek(fp,8L,SEEK_SET);
	fseek(fp1,16L,SEEK_SET);
	for(index=0;index<60000;index++){
		if(index%5000==0){
			printf("read %d/60000 images\n",index);
		}
		for(i=0;i<28*28;i++){
			fread(temp,1,1,fp1);
			trainpixel[index][i] = 255-*temp;
		}
		fread(label,1,1,fp);
		trainlabel[index]=*label;
	}
	printf("read 60000/60000 images\n");

	fseek(fp2,8L,SEEK_SET);
	fseek(fp3,16L,SEEK_SET);
	for(index=0;index<10000;index++){
		if(index%5000==0){
			printf("read %d/10000 images\n",index);
		}
		for(i=0;i<28*28;i++){
			fread(temp,1,1,fp3);
			testpixel[index][i] = 255-*temp;
		}
		fread(label,1,1,fp2);
		testlabel[index]=*label;
	}
	printf("read 10000/10000 images\n");


/// train
//
//forward
	int t=0;
	double sum=0;
	double error=0;
	printf("forward\n");
	int p=0;
	double max=0;
	int maxindex=0;
	int tcorr=0;
	int tcorr1=0;
	int corr=0;
	int corr1=0;
	srand(time(NULL));
	for(i=0;i<785;i++){
		for(j=0;j<10;j++){
	weight[i][j] = (float)((rand()%200/100.0)-1)/100.0;  //(-1,1)
		}
simple[i] = (float)((rand()%200/100.0)-1)/100.0; //(-1,1)
	}
	
	for(p=0;p<epoch;p++){
		corr=0;
		corr1=0;
		for(k=0;k<60000;k++){
			for(i=0;i<28*28;i++){
				neuron[i] = (double)trainpixel[k][i]/255;
			}
			neuron[784]=-1;
			//forwarding
			sum=0;
			for(i=0;i<=28*28;i++){
				sum+= neuron[i]*simple[i];
			}
			if(sum>=0){
				out=1;
			}
			else{
				out=0;
			}
			for(j=0;j<10;j++){
				sum=0;
				for(i=0;i<=28*28;i++){
					sum+= weight[i][j]*neuron[i];
				}
				if(sum>=0){
					outlayer[j] =1;
				}
				else{
					outlayer[j]=0;
				}
			}
			max =outlayer[0];
			maxindex = 0;
			for(i=0;i<10;i++){
				if(outlayer[i]>=max){
					max = outlayer[i];
					maxindex = i;
				}
			}
			if(maxindex == trainlabel[k]){
				corr++;
			}
			if((out==10&& trainlabel[k]==3) ||(out==0 && trainlabel[k]!=3)){
				corr1++;
			}
			if(k%5000==0 && k>0){
				printf("%d / 60000 %d / %d in training \n",k,p+1,epoch);
				printf("accuracy for \"is a tree"": %f % \n",corr1/(float)k*100);
				printf("accuracy for \"ten perceptrons"": %f % \n",corr/(float)k*100);
			}
			//backpropogation
			for(i=0;i<=28*28;i++){
				for(j=0;j<10;j++){
					if(j == trainlabel[k]){
						weight[i][j] += learningrate*(1-outlayer[j])*0.5*neuron[i];
					}
					else{
						weight[i][j] += learningrate*(0-outlayer[j])*0.5*neuron[i];
					}
				}
			}
			for(i=0;i<=28*28;i++){
				if(trainlabel[k]==3){
					simple[i] += learningrate*(1-out)*neuron[i]*0.5;
				}
				else{
					simple[i] += learningrate*(0-out)*neuron[i]*0.5;
				}
			}

		}
		tcorr=tcorr1=0;
		for(k=0;k<10000;k++){
			for(i=0;i<28*28;i++){
				neuron[i] = (double)testpixel[k][i]/255;
			}
			sum=0;
			for(i=0;i<=28*28;i++){
				sum+= neuron[i]*simple[i];
			}
			if(sum>=0){
				out=1;
			}
			else{
				out=0;
			}
			for(j=0;j<10;j++){
				sum=0;
				for(i=0;i<=28*28;i++){
					sum+= weight[i][j]*neuron[i];
				}
				if(sum>=0){
					outlayer[j] =1;
				}
				else{
					outlayer[j]=0;
				}
			}
			max =outlayer[0];
			maxindex = 0;
			for(i=0;i<10;i++){
				if(outlayer[i]>=max){
					max = outlayer[i];
					maxindex = i;
				}
			}
			if(maxindex == testlabel[k]){
				tcorr++;
			}
			if((out==10&& testlabel[k]==3) ||(out==0 && testlabel[k]!=3)){
				tcorr1++;
			}
			if(k%5000==0 && k>0){
				printf("%d / 10000 %d / %d in test\n",k,p+1,epoch);
				printf("In test accuracy for \"is a tree"": %f % \n",tcorr1/(float)k*100);
				printf("In test accuracy for \"ten perceptrons"": %f % \n",tcorr/(float)k*100);
			}
		}

	//
	}
	double min=1;
	max = -1;
	
	for(i=0;i<28*28;i++){
		if(simple[i]<=min){
			min=simple[i];
		}
		if(simple[i]>=max){
			max = simple[i];
		}
	}
	if(max!=min){
		for(i=0;i<28*28;i++){
			simple[i]-=min;
			simple[i]*= (255/(max-min));
		}
	}
	FILE* feature;
	feature = fopen("Feature.pgm","wb");
	fprintf(feature,"P2\n#Feature of perceptron\n28 28\n255\n");
	for(i=0;i<28*28;i++){
		fprintf(feature,"%d ",(int)simple[i]);
	}
	fclose(feature);
// test
	for(i=0;i<60000;i++){
		free(trainpixel[i]);
	}
	for(i=0;i<10000;i++){
		free(testpixel[i]);
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	free(trainlabel);
	free(trainpixel);
	free(testpixel);
	free(testlabel);
	free(label);
	free(temp);

	return 0;
}
double sigmoid(double x){
	return 1/(1+exp(-x));
};

float dsigmoid(float x){
	return sigmoid(x)*(1-sigmoid(x));
};

