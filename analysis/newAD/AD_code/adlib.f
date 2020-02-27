
		SUBROUTINE LOG1
		COMMON /DATA/ FACLOG(170)
C		SUBROUTINE FOR GENERATING LOG OF FACTORIALS
C		UP TO 169
		FACLOG(1)=0.0
		FACLOG(2)=0.0
		DO 10 I=3,170
		  RI=I-1
		  FACLOG(I)=ALOG(RI)+FACLOG(I-1)
10		CONTINUE
		RETURN
		END
C
C
C
C
		FUNCTION RACAH(A)
C
C		Assumes that the LN of N! is in FACLOG(N+1)
C
		DIMENSION A(6),II(6),IX(6),KK(8)
		COMMON /DATA/ FACLOG(170)
		DIMENSION NN(4),NX(12),NY(8)
		EQUIVALENCE (KK(1),K1),(KK(2),K2),(KK(3),K3),
     +       (KK(4),K4),(KK(5),K5),(KK(6),K6),(KK(7),K7),
     +       (KK(8),K8)
		EQUIVALENCE (II(1),IA),(II(2),IB),(II(3),IC),
     +        (II(4),ID)   
		EQUIVALENCE (II(5),IE),(II(6),IF)
		EQUIVALENCE (KK(1),NY(1)),(LMIN,NZMIN),(KMIN,NZMAX),
     +       (KQ,NZM1),(K0,I1)
		RACAH=0.0
		DO 101 I=1,6
101		  II(I)=A(I)*2.0
		K1=IA+IB-IE
		K3=IC+ID-IE
		K5=IA+IC-IF
		K7=IB+ID-IF
		K2=IE-IABS(IA-IB)
		K4=IE-IABS(IC-ID)
		K6=IF-IABS(IA-IC)
		K8=IF-IABS(IB-ID)
		K0= MIN0(K1,K2,K3,K4,K5,K6,K7,K8)
		IF (K0.LT.0) GOTO 199
		DO 106 I=1,7,2
		  NKK=KK(I)
		  N2KK=KK(I)/2
		  NKK2=N2KK*2
		  IF(NKK.NE.NKK2) GOTO 199
106		CONTINUE
		IX(1)=IA
		IX(2)=ID
		IX(3)=IB
		IX(4)=IC
		IX(5)=IF
		IX(6)=IE
		LMIN=IX(1)
		KMIN=1
		DO 110 I=2,6
		  IF (IX(I)-LMIN)  108,109,110
108		  LMIN=IX(I)
109		  KMIN=I
110		CONTINUE
C
C
C
		SGN1=1.0
		GO TO (115,115,120,120,125,130),KMIN
115		 KQ=7-KMIN
		IA=IX(KQ)
		ID=IX(KMIN+4)
		IE=IX(KMIN)
		IF=IX(KQ-4)
		IF (MOD((IA+ID-IE-IF)/2,2).NE.0) SGN1= -1.0
		GO TO 130
120		KQ=9-KMIN
		IB=IX(KQ)
		IC=IX(KMIN+2)
		IE=IX(KMIN)
		IF=IX(KQ-2)
		IF (MOD((IB+IC-IE-IF)/2,2).NE.0) SGN1=-1.0
		GOTO 130
125		IE=IX(5)
		IF=IX(6)
		IB=IX(4)
		IC=IX(3)
130		IP=IA-IB
		IQ=IC-ID
		IF (IABS(IP).GE.IABS(IQ)) GOTO 135
		IT=IC
		IC=IA
		IA=IT
		IT=ID
		ID=IB
		IB=IT
		IP=IQ
135		IF (IP.GE.0)GOTO 140
		IT=IB
		IB=IA
		IA=IT
		IT=ID
		ID=IC
		IC=IT
		IP=-IP
140		IQ=IC-ID
		SGN2=1.0
                IF (MOD((IB+ID-IF)/2,2).NE.0) SGN2=-1.0
		IF (IE.GT.0) GOTO 150
		BI=IB
		DI=ID
		RACAH=SGN1*SGN2/SQRT((BI+1.0)*(DI+1.0))
		GOTO 190
150		NN(1)=(IA+IB+IE)/2+1
		NN(2)=(IC+ID+IE)/2+1
		NN(3)=(IA+IC+IF)/2+1
		NN(4)=(IB+ID+IF)/2+1
		NX(1)=NN(1)-IE
		NX(2)=NN(1)-IB
		NX(3)=NN(1)-IA
		NX(4)=NN(2)-IE
		NX(5)=NN(2)-ID
		NX(6)=NN(2)-IC
		NX(7)=NN(3)-IF
		NX(8)=NN(3)-IC
		NX(9)=NN(3)-IA
		NX(10)=NN(4)-IF
		NX(11)=NN(4)-ID
		NX(12)=NN(4)-IB
		IP=(IA+IB+IC+ID+4)/2
		IQ=(IE+IF-IA-ID)/2
		IT=(IE+IF-IB-IC)/2
		NZMIN=MAX0(1,-IQ+1)
		NZMAX=MIN0(NX(1),NX(4),NX(10))
		IF (NZMAX.LT.NZMIN) GOTO 190
		SQLOG=0
		DO 171 I=1,4
		  I1=NN(I)+1
171		SQLOG=SQLOG-FACLOG(I1)
		DO 173 I=1,12
		I1=NX(I)
173		SQLOG=SQLOG+FACLOG(I1)
		SQLOG=0.5*SQLOG
		SSS=0.0
		DO 180 NZ=NZMIN,NZMAX
		NZM1=NZ-1
		NY(1)=IP-NZM1
		NY(2)=NX(1)-NZM1
		NY(3)=NX(4)-NZM1
		NY(4)=NX(7)-NZM1
		NY(5)=NX(10)-NZM1
		NY(6)=NZ
		NY(7)=IQ+NZ
            NY(8)=IT+NZ
		I1=NY(1)
		SSLOG=SQLOG+FACLOG(I1)
		DO 185 I=2,8
		I1=NY(I)
185		SSLOG=SSLOG-FACLOG(I1)
		SSS=SSS+((-1.0)**NZM1)*EXP(SSLOG)
180		CONTINUE
		RACAH=SGN1*SSS
190		CONTINUE
199		RETURN
		END
C
C
		FUNCTION CLEB(A)
C
C		ASSUMES THAT THE LOG(BASE E) OF N! IS IN FACLOG(N+1)
C
		COMMON /DATA/ FACLOG(170)
		DIMENSION A(6),II(6),IM(6),IX(9),NX(5)
		EQUIVALENCE (II(1),IA),(II(2),IB),(II(3),IC),(II(4),ID)
		EQUIVALENCE (II(5),IE), (II(6),IF)
		DO 101 I=1,6
101		  II(I)=2.0*A(I)
		CLEB=0.0
		IF(ID+IE-IF.NE.0)GOTO 199
		K0=IA+IB+IC
		IF(MOD(K0,2).NE.0) GOTO 199
		K1=IA+IB-IC
		K2=IC+IA-IB
		K3=IB+IC-IA
		K4=IA-IABS(IB-IC)
		K5= IB-IABS(IC-IA)
		K6=IC-IABS(IA-IB)
		K7=MIN0(K1,K2,K3,K4,K5,K6)
		IF(K7.LT.0) GOTO 199
		DO 115 I=1,3
		  IF(MOD(II(I)+II(I+3),2).NE.0)GO TO 199
		  IF(II(I).LT.IABS(II(I+3))) GOTO 199
115		CONTINUE
		SGNFAC=1.0
		DO 116 I=1,6
116		  IM(I)=II(I)
		IF(IA.GE.IB) GOTO 120
		IF(IA.GE.IC) GOTO 125
		IT=IA
		IA=IB
		IB=IT
		IT=ID
		ID=IE
		IE=IT
		IF(MOD(K1/2,2).NE.0) SGNFAC=-1.0
		GOTO 135
120 	IF(IC.GE.IB) GO TO 135
125		IT=IC
		IC=IB
		IB=IT
		IT=IF
		IF=-IE
		IE=-IT
		SGNFAC=SQRT((2.0*A(3)+1.0)/(2.0*A(2)+1.0))
		IF(MOD((IM(1)-IM(4))/2,2).NE.0)SGNFAC=-SGNFAC
135		IF(IB.NE.0) GOTO 140
		CLEB=SGNFAC
		GOTO 190
140		IF(IE.LT.0) GOTO 150
		ID=-ID
		IE=-IE
		IF=-IF
		IF(MOD((IA+IB-IC)/2,2).NE.0)SGNFAC=-SGNFAC
150		FC2=IC+1
		IT=K0/2+1
		IX(1)=IT-IC
		IX(2)=IT-IB
		IX(3)=IT-IA
		IX(4)=(IA+ID)/2+1
		IX(5)=IX(4)-ID
		IX(6)=(IB+IE)/2+1
		IX(7)=IX(6)-IE
		IX(8)=(IC+IF)/2+1
		IX(9)=IX(8)-IF
		SQFCLG=ALOG(FC2)-FACLOG(IT+1)
		DO 160 I=1,9
		IXI=IX(I)
		SQFCLG=SQFCLG+FACLOG(IXI)
160		CONTINUE
		SQFCLG=0.5*SQFCLG
		NZMAX=MIN0(IX(1),IX(5),IX(6))
		NZ2=(IB-IC-ID)/2
		NZ3=(IA-IC+IE)/2
		NZMIN=MAX0(0,NZ2,NZ3)+1
		IF(NZMAX.LT.NZMIN)GOTO 190
		SS=0.
		S1=(-1.0)**(NZMIN-1)
		DO 180 NZ=NZMIN,NZMAX
		  NZM1=NZ-1
		  NX(1)=IX(1)-NZM1
		  NX(2)=IX(5)-NZM1
		  NX(3)=IX(6)-NZM1
		  NX(4)=NZ-NZ2
		  NX(5)=NZ-NZ3
		TERMLG=SQFCLG-FACLOG(NZ)
		    DO 175 I=1,5
		        IXI=NX(I)
175			TERMLG=TERMLG-FACLOG(IXI)
			SS=SS+S1*EXP(TERMLG)
180			S1=-S1
			CLEB=SGNFAC*SS
190		CONTINUE
199		RETURN
		END
C
C
		SUBROUTINE QK(E,QD2,QD4,R, D, T )
C
C
C		THIS ROUTINE CALCULATES THE ANGULAR DISTRIBUTIONS
C		ATTENUATION COEFFICIENTS AS DEFINED BY ROSE FOR
C		CYLINDRICAL GE(LI) DETECTORS
C
		EMEV=E/1000
		ELN=LOG(EMEV)
		EL1=ELN
		EL2=ELN**2
		EL3=EL1*EL2
		EL4=EL2**2
		EL5=EL4*EL1
		TLN=-1.1907-.5372*EL1-.043*EL2+.0218*EL3+
     1           .0765*EL4+.0095*EL5
		TAU=EXP(TLN)
C
		Z1=R/(D+T)
		Z2=R/D
		ALPHA=ATAN(Z1)
		GAMMA=ATAN(Z2)
C
		BL=0
		BU=ALPHA
		DELX1=(BU-BL)/1000
		SUM1=0
		SUM2=0
		SUM3=0
C
		DO 100 I=0,1000
C
		   IF(I.NE.0) GOTO 10
		   A=1.0
		   GO TO 50
10		   IF(I.NE.1000) GOTO 20
		   A=1.0
		   GO TO 50
20		   J=MOD(I,2)
		   IF(J.EQ.0) GOTO 30
		   A=4.0
		   GOTO 50
30                 A=2.0
50		   BETA=BL+I*DELX1
C
		   COSB=COS(BETA)
		   SINB=SIN(BETA)
		   SECB=1.0/COSB
		   C2=COSB**2
		   C4=COSB**4
		   FAC1=-1*TAU*T*SECB
		   EX1=EXP(FAC1)
C
		  TERM1=.5*(3*C2-1)*(1-EX1)*SINB*A*DELX1
		  TERM2=.125*A*(35*C4-30*C2+3)*(1-EX1)*SINB*DELX1
		TERM3=A*(1-EX1)*SINB*DELX1
C
		  SUM1=SUM1+TERM1
		  SUM2=SUM2+TERM2
		  SUM3=SUM3+TERM3
C
100		CONTINUE
C
		ANS1=SUM1/3
		ANS2=SUM2/3
		ANS3=SUM3/3
C
C
		BL=ALPHA
		BU=GAMMA
		DELX2=(BU-BL)/1000
		SUM4=0
		SUM5=0
		SUM6=0
C
		DO 105 I=0,1000
C
		   IF(I.NE.0) GO TO 60
		   A=1.0
		   GOTO 90
60		IF(I.NE.1000) GOTO 70
		   A=1.0
		   GOTO 90
70		   J2=MOD(I,2)
		   IF (J2.EQ.0) GOTO 80
		   A=4.0
		   GOTO 90
80		   A=2.0
90		   BETA=BL+I*DELX2
C
		  COSB=COS(BETA)
		  SINB=SIN(BETA)
		  SECB=1.0/COSB
		  CSCB=1.0/SINB
		  FAC2=-1*TAU*(R*CSCB-D*SECB)
		  EX2=EXP(FAC2)
		  C2=COSB**2
		  C4=COSB**4
C
		TERM4=.5*A*(3*C2-1)*(1-EX2)*SINB*DELX2
		TERM5=.125*A*(35*C4-30*C2+3)*(1-EX2)*SINB*DELX2
		TERM6=A*(1-EX2)*SINB*DELX2
C
		   SUM4=SUM4+TERM4
		   SUM5=SUM5+TERM5
		   SUM6=SUM6+TERM6
C
105		CONTINUE
C
	        ANS4=SUM4/3
		ANS5=SUM5/3
		ANS6=SUM6/3
C
C		CALCULATE Q2 AND Q4
C
		QD2=(ANS1+ANS4)/(ANS3+ANS6)
		QD4=(ANS2+ANS5)/(ANS3+ANS6)
C
	open (4, file = 'ad.rdt', status ='unknown', form ='formatted')
		WRITE(4,910) R,D,T
910		FORMAT(' R(CM)=',F10.5,2X,'D(CM)=',F10.5,2X,
     +      ' T(CM)=',F10.5)
		WRITE(4,920) E,TAU
920		FORMAT(' GAMMA ENERGY=',F6.1,'KEV',2X,' ATTEN COEFF=',
     +      F10.5,' INVERSE CM')
		WRITE (4,930) QD2,QD4
930		FORMAT(' Q2=',F10.5,2X,' Q4=',F10.5)
	close (4)
C
		RETURN
C
		END