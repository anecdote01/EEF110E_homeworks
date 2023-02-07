//
//  main.c
//  SecondAssignment_XCode
//
//  Created by Mehmet Soner Korucu on 24.12.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// all q variables below represent router's queue
int q1 = 0;
int q2 = 0;
int q3 = 0;
int q4 = 0;
//router arrays. I designed them as 2500-4 since maximum possible number of packets that can be queued is 2500. Second dimension represents queue,ip address, length, priority. queue inside second dimension is 1 greater then the queue variable. It means that queue inside second dimension starts from 1.
int router1[2500][4];
int router2[2500][4];
int router3[2500][4];
int router4[2500][4];
//variables below are for calculating total length of queued packets in router.
int lengthOfR1 =0;
int lengthOfR2 =0;
int lengthOfR3 =0;
int lengthOfR4 =0;
// total enqueue , dequeue and drop amounts.
int TotalEnqueue= 0;
int TotalDequeue = 0;
int TotalDrop = 0;
//defining a simple struct model for packets. Only Enqueue will call it and generate random packets.
struct packet{
    int dst_ip; /* defining pointer destination ip*/
    int len; /*defining pointer length*/
    int priority; /* defining pointer priority 0 or 1*/
};

void dequeue(void)
{
    //ip1 stands for the significant part of original ip adress (20-12-50-70).
    int ip1 = (rand() % 4 );
    switch(ip1)
    {
        case 0: ip1 = 100020000; break;
        case 1: ip1 = 100012000; break;
        case 2: ip1 = 100050000; break;
        case 3: ip1 = 100070000;  break;
    }
    //I designed dequeue function to dequeue randomly like enqueue function since it is not spesified clearly in assignment paper. it will randomly determine a router to dequeue its packet from head to tail.
    if (ip1 == 100020000)
    {
        int i = 0;
        //to prevent negative queue, I simply added this condition
        if(q1>0)
        {
            //for loop will shift 1 lane.
            lengthOfR1 -= router1[i][2];
            for(int j = q1;j>i;i++)
            {
                router1[i][1] = router1[i+1][1];
                router1[i][2] = router1[i+1][2];
                router1[i][3] = router1[i+1][3];
            }
            q1--;
            //line below is also for tests.
            //printf("router1 dequeued. new line is: %d\n",q1);
            TotalDequeue++;
        }
    }
    //other conditions are the copies of first condition except variables re-arranged.
    else if(ip1 == 100012000)
    {
        int i=0;
        if(q2>0)
        {
            lengthOfR2 -= router1[i][2];
            for(int j = q2;j>i;i++)
            {
                router2[i][1] = router2[i+1][1];
                router2[i][2] = router2[i+1][2];
                router2[i][3] = router2[i+1][3];
            }
            q2--;
            //printf("router2 dequeued. new line is: %d\n",q2);
            TotalDequeue++;
        }
    }
    else if(ip1 == 100050000)
    {
        int i = 0;
            if(q3>0)
            {
                lengthOfR3 -= router1[i][2];
                for(int j = q3;j>i;i++)
                {
                    router3[i][1] = router3[i+1][1];
                    router3[i][2] = router3[i+1][2];
                    router3[i][3] = router3[i+1][3];
                }
                q3--;
                //printf("router3 dequeued. new line is: %d\n",q3);
                TotalDequeue++;
            }
    }
    else if(ip1 == 100070000)
    {
        int i = 0;
        if(q4>0)
        {
            lengthOfR4 -= router1[i][2];
            for(int j = q4;j>i;i++)
            {
                router4[i][1] = router4[i+1][1];
                router4[i][2] = router4[i+1][2];
                router4[i][3] = router4[i+1][3];
            }
            q4--;
            //printf("router2 dequeued. new line is: %d\n",q4);
            TotalDequeue++;
        }
    }
}
//prio represents the priority of packet that has just been generated in dequeue function. FSIp represents first significant ip like 20-12-50-70
void drop(int FSIp,int Prio,int length, int DestIp)
{
    //If priority of the generated packet is low, function will skip the packet.
    if(FSIp == 100020000 && Prio ==1)
    {
    	//this loop will check if there is a packet that has low priority from tail to head
        for(int i = 0, j=(q1-1); j>=i;j--)
        {
        	// searching for low priority. j>=0 is for precausion
            if(router1[j][3] == 0 && j>=0)
            {
            	// decreasing length
                lengthOfR1 -= router1[j][2];
                // line below is for test. you can uncomment it to observe outputs
                //printf("low priority packet will be dropped on router1. Total length will be %d\n",lengthOfR1+length);
                for(;j<q1;j++)
                {
                    router1[j][1] = router1[j+1][1];
                    router1[j][2] = router1[j+1][2];
                    router1[j][3] = router1[j+1][3];
                }
                TotalDrop++;
                q1--;
                // this condition is also for tests.
                if (lengthOfR1+ length >=1000000)
                {
                    //printf("new packet exceeds maximum capasity of router1!\n");
                }
                //adding new packet to queue
                else if(lengthOfR1 + length <1000000)
                {
                    lengthOfR1 += length;
                    router1[q1][0] = q1+1;
                    router1[q1][1]=DestIp;
                    router1[q1][2]= length;
                    router1[q1][3] = Prio;
                    TotalEnqueue++;
                    //line below is for test
                    //printf("new packet has been added succsessfully into router1!\n");
                    q1++;
                    break;
                }

            }
        }
    }
    //next lines are copies of the first condition
    else if(FSIp == 100012000 && Prio ==1)
    {
        for(int i = 0, j=(q2-1); j>=i;j--)
        {
            if(router2[j][3] == 0 && j>=0)
            {
                lengthOfR2 -= router2[j][2];
                //printf("low priority packet will be  dropped on router2 . Total length will be %d\n",lengthOfR2+length);
                for(;j<q2;j++)
                {
                    router2[j][1] = router2[j+1][1];
                    router2[j][2] = router2[j+1][2];
                    router2[j][3] = router2[j+1][3];
                }
                TotalDrop++;
                q2--;
                if (lengthOfR2+ length >=1000000)
                {
                    //printf("new packet exceeds maximum capasity of router2!\n");
                }
                else if(lengthOfR2+ length <1000000)
                {
                    lengthOfR2 += length;
                    router2[q2][0] = q2+1;
                    router2[q2][1]=DestIp;
                    router2[q2][2]= length;
                    router2[q2][3] = Prio;
                    TotalEnqueue++;
                    //printf("new packet has been added succsessfully into router2!\n");
                    q2++;
                    break;
                }

            }
        }
    }
    else if(FSIp == 100050000 && Prio ==1)
    {
        for(int i = 0, j=(q3-1); j>=i;j--)
        {
            if(router3[j][3] == 0 && j>=0)
            {
                lengthOfR3 -= router3[j][2];
                //printf("low priority packet will be  dropped on router3 . Total length will be %d\n",lengthOfR3+length);
                for(;j<q3;j++)
                {
                    router3[j][1] = router3[j+1][1];
                    router3[j][2] = router3[j+1][2];
                    router3[j][3] = router3[j+1][3];
                }
                TotalDrop++;
                q3--;
                if (lengthOfR3+ length >=1000000)
                {
                    //printf("new packet exceeds maximum capasity of router3!\n");
                }
                else if(lengthOfR3+ length <1000000)
                {
                    lengthOfR3 += length;
                    router3[q3][0] = q3+1;
                    router3[q3][1]=DestIp;
                    router3[q3][2]= length;
                    router3[q3][3] = Prio;
                    TotalEnqueue++;
                    //printf("new packet has been added succsessfully into router3!\n");
                    q3++;
                    break;
                }

            }
        }
    }
    else if(FSIp == 100070000 && Prio ==1)
    {
        for(int i = 0, j=(q4-1); j>=i;j--)
        {
            if(router4[j][3] == 0 && j>=0)
            {
                lengthOfR4 -= router4[j][2];
                //printf("Low priority packet will be  dropped on router4 . Total length will be %d\n",lengthOfR4+length);
                for(;j<q4;j++)
                {
                    router4[j][1] = router4[j+1][1];
                    router4[j][2] = router4[j+1][2];
                    router4[j][3] = router4[j+1][3];
                }
                TotalDrop++;
                q4--;
                if (lengthOfR4+ length >=1000000)
                {
                    //printf("new packet exceeds maximum capasity of router4!\n");
                }
                else if(lengthOfR4+ length <1000000)
                {
                    lengthOfR4 += length;
                    router4[q4][0] = q4+1;
                    router4[q4][1]=DestIp;
                    router4[q4][2]= length;
                    router4[q4][3] = Prio;
                    TotalEnqueue++;
                    //printf("new packet has been added succsessfully into router4!\n");
                    q4++;
                    break;
                }

            }
        }
    }

}
void enqueue(void)
{
    //first, we need to create random packets
    //randomly finding the significant ip (20-12-50-70)
    int ip1 = (rand() % 4 );
    switch(ip1)
    {
        case 0: ip1 = 100020000; break;
        case 1: ip1 = 100012000; break;
        case 2: ip1 = 100050000; break;
        case 3: ip1 = 100070000;  break;
    }
    //ip2 stands for second significant ip. generates ip from 1 to 254.
    int ip2 = (rand() % 254 )+ 1;
    int l = (rand() % 1000 )+ 500;
    int p = (rand() % 2 );
    //basicly defining generated variables into the struct packet. whenever enqueue called, it will generate new variables therefore new packets
    struct packet insidePacket = {(ip1+ip2),l,p};

    //in this part, function will control first significant ip and will put the packet into router queue.
    if (ip1 == 100020000)
    {
        //increasing length of packet. we will determine if we should add new packet into the router.
        lengthOfR1 += insidePacket.len;
        //if total length is below 1MB when new packet is added, it will start writing new packet into the router.
        if(lengthOfR1 <1000000)
        {
            //adding new packet into the router.
            router1[q1][0] = q1+1;
            router1[q1][1]=insidePacket.dst_ip;
            router1[q1][2]= insidePacket.len;
            router1[q1][3] = insidePacket.priority;
            //for loop below is for tests. you can uncomment them to observe outputs
            for(int y=0;y<4;y++)
            {
            //  printf("%d\t",router1[q1][y]);
            }
            //printf("\n");

            //Increasing queue variable to be able to add new packets
            q1++;
            //this variable will increase whenever function enqueues new packets. It is also for tests.
            TotalEnqueue++;
        }
        //if total length if above 1mb when new packet is added, it will  decrease the length of that packet from total length, then call drop function.
        else if(lengthOfR1 >=1000000)
        {
            lengthOfR1 -= insidePacket.len;
            drop(ip1,p,l,insidePacket.dst_ip);
        }
    }
    //other conditions are the copies of first condition except variables re-arranged.
    else if (ip1 == 100012000)
    {
        lengthOfR2 += insidePacket.len;
        if(lengthOfR2 <1000000)
        {
            router2[q2][0] = q2+1;
            router2[q2][1]=insidePacket.dst_ip;
            router2[q2][2]= insidePacket.len;
            router2[q2][3] = insidePacket.priority;
            for(int y=0;y<4;y++)
            {
            //    printf("%d\t",router2[q2][y]);
            }
            //printf("\n");
            q2++;
            TotalEnqueue++;
        }
        else if(lengthOfR2 >=1000000)
        {
            lengthOfR2 -= insidePacket.len;
            drop(ip1,p,l,insidePacket.dst_ip);
        }
    }
    else if (ip1 == 100050000)
    {
        lengthOfR3 += insidePacket.len;
        if(lengthOfR3 <1000000)
        {
            router3[q3][0] = q3+1;
            router3[q3][1]=insidePacket.dst_ip;
            router3[q3][2]= insidePacket.len;
            router3[q3][3] = insidePacket.priority;
            for(int y=0;y<4;y++)
            {
            //    printf("%d\t",router3[q3][y]);
            }
            //printf("\n");
            q3++;
            TotalEnqueue++;
        }
        else if(lengthOfR3 >=1000000)
        {
            lengthOfR3 -= insidePacket.len;
            drop(ip1,p,l,insidePacket.dst_ip);
        }
    }
    else if (ip1 == 100070000)
    {
        lengthOfR4 += insidePacket.len;
        if(lengthOfR4 <1000000)
        {
            router4[q4][0] = q4+1;
            router4[q4][1]=insidePacket.dst_ip;
            router4[q4][2]= insidePacket.len;
            router4[q4][3] = insidePacket.priority;
            for(int y=0;y<4;y++)
            {
            //    printf("%d\t",router4[q4][y]);
            }
            //printf("\n");
            q4++;
            TotalEnqueue++;
        }
        else if(lengthOfR4 >=1000000)
        {
            lengthOfR4 -= insidePacket.len;
            drop(ip1,p,l,insidePacket.dst_ip);
        }

    }

}

int main(void) {
    //i is for while loop
    int i = 1;
    //variable that are used for time arrangements
    int endingTime;
    // I defined congestionRatio in a different way. It still works fine.
    int congestionRatio,EnqueueRate,DequeueRate;
    //getting the inputs of time and ratio.
    printf("please type an ending time in seconds: ");
    scanf("%d",&endingTime);
    printf("please type an congestion ratio from 0 to 100: ");
    scanf("%d",&congestionRatio);
    //i used 50000 to increase cycle and decrease generating.
    EnqueueRate = 50000;
    //if congestionRatio is 0, i will start a different while loop below. You will see.
    if(congestionRatio != 0)
    {
        DequeueRate = (EnqueueRate*100)/congestionRatio;
    }
    srand(time(NULL));
    //time variables
    time_t endwhile , interval;
    time_t start = time(NULL);
    // end loop after this time has elapsed
    time_t seconds = endingTime;
    //these 2 variables below will be used in while conditions.
    endwhile = start + seconds;
    interval = start + 1;
    //if congestionratio is 0, it won't execute dequeue function
    if(congestionRatio == 0)
    {
       while(start < endwhile)
        {
            // in every 50000 cycle, if condition will execute.
            if(i % EnqueueRate == 0)
            {
                enqueue();
            }
            i++;
            // it will update time and will stop loop when time is up.
            start = time(NULL);
            //every 1 second condition.
            while(start>=interval)
            {
                int TotalLength = lengthOfR1 + lengthOfR2 + lengthOfR3 + lengthOfR4;
                printf("//////////////////////////////////////////////////////\n");
                printf("router 1 queue: %d\t\trouter 2 queue: %d\nrouter 3 queue: %d\t\trouter 4 queue: %d\nTotal queue: %d\n",q1,q2,q3,q4,(q1+q2+q3+q4));
                printf("router 1 length: %d\t\trouter 2 length: %d\nrouter 3 length: %d\t\trouter 4 length: %d\n\t\tTotal length: %d\n",lengthOfR1,lengthOfR2,lengthOfR3,lengthOfR4,TotalLength);
                // total length will be equal to the total enqueue - (total dequeue + total drop)
                printf("Total Enqueuing: %d\tTotal Dequeuing: %d\tTotal Drop: %d\n\n",TotalEnqueue,TotalDequeue,TotalDrop);
                interval++;
            }
        }
    }
    //else will execute dequeue and enqueue in harmony
    else
    {
        while(start < endwhile)
        {
            //dequeue rate works just like assignment asked for.
            if(i%(DequeueRate)==0)
            {
            dequeue();
            }
            if(i % EnqueueRate == 0)
            {
                enqueue();
            }
            i++;
            //it will update time and will stop loop when time is up.
            start = time(NULL);
            while(start>=interval)
            {
                int TotalLength = lengthOfR1 + lengthOfR2 + lengthOfR3 + lengthOfR4;
                printf("//////////////////////////////////////////////////////\n");
                printf("router 1 queue: %d\t\trouter 2 queue: %d\nrouter 3 queue: %d\t\trouter 4 queue: %d\nTotal queue: %d\n",q1,q2,q3,q4,(q1+q2+q3+q4));
                printf("router 1 length: %d\t\trouter 2 length: %d\nrouter 3 length: %d\t\trouter 4 length: %d\n\t\tTotal length: %d\n",lengthOfR1,lengthOfR2,lengthOfR3,lengthOfR4,TotalLength);
                // total length will be equal to the total enqueue - (total dequeue + total drop)
                printf("Total Enqueuing: %d\tTotal Dequeuing: %d\tTotal Drop: %d\n\n",TotalEnqueue,TotalDequeue,TotalDrop);
                interval++;
            }

        }
    }


     //I designed a simple loop for supervisor to check the packets inside router. you can simply oberve any router by changing variables.
/*
    for( int r = 0;r<q1;r++)
    {
        printf("%d\t%d\t%d\t%d\n",router1[r][0],router1[r][1],router1[r][2],router1[r][3]);
    }
*/


}


