
	Subroutine PLOTdata 

c	Subroutine PLOTdata to plot data generated by the Angular 
c	Distribution Program AD.

	include 'ad.inc'

	dimension x(100), y(100), er(100), kin(6)
	dimension angle(10), yield(10), sigmay(10), ftest(10), 
     +		  yfit(10), a(10), sigmaa(10), b(10), sigmab(10)	

	include 'keys.inc'
 
c----------------------------------------------------------------------

	  lin = 0				! linear plot.
	  xmin = 0.
	  xmax = 90.
	  npts = 91

c----------------------------------------------------------------------

c  Added 12-28-2005 by SLT to fix wierd plots due to strange a coeffs
	  do is = 1,10
	     a(is) = 0.
	     end do
c End add 12-28-2005

	write(6,*)' Enter # of set you want to plot:'
	read(5,*) numset
	k = numset
 100	idelta = int( deltamin(k) ) + 91

	a(1) = 1
	if (atwo(k,idelta) .ne. 0.) then
	  a(3) = atwo(k,idelta )
	  a(5) = afour(k,idelta )
	end if
	  if (a(3) .eq. 0. .and. a(5) .eq. 0. ) then
	    write (6,*) ' Enter A2 and A4: '
	    read (5,*) a(3), a(5)
	  end if	    
	  do i=1,npts
	    x(i) = i - 1
	  end do

	  call legendre ( x, y, a, npts )

*	if (ynorm .eq. 0.) then
	  a3 = a(3)
	  a5 = a(5)
	  call legnorm (a3, a5, yth, ynorm)
*	end if
*	  do i=1,npts
*	  y(i) = ynorm * y(i)
*	  end do

c	  do i=1,10
c	  write (3,*) x(i), y(i), a(i)
c	  end do
c         TYPE *, YNORM        !CARL
	  ymax = -1e+10
	  ymin = 1e+10
	  do i = 1,npts
	    if ( y(i) .gt. ymax ) ymax = y(i) 
	    if ( y(i) .lt. ymin ) ymin = y(i) 
	  end do
	  do i = 1,lmax
	    y(i) = (yexp(i) + yerr(i)) / ynorm
	    if ( y(i) .gt. ymax ) ymax = y(i) 
	    if ( y(i) .lt. ymin ) ymin = y(i) 
	  end do
	  if ( ymin .gt. 0. ) ymin = 0.
	  ymax = 1.1 * ymax
	  if (ymax .lt. 2) ymax = 2.
c         TYPE *, YNORM,YMAX      !CARL
	  call anmode
*	  WRITE(6,*)ymin,ymax
*	  read (5,*) inum

	kind = 0
 
	mode = 1
	nsxtic = 9
	nsytic = 9
	double = 0.
	jpass = 1
*        TYPE *, YNORM,YMAX
c	write (3,*) mode, xmin, xmax, nsxtic, ymin, ymax, nsytic
300	call frame (mode, xmin, xmax, nsxtic, ymin, ymax, nsytic, double,
     +  jpass)
c	write (3,*) 'back from frame'
	do 28 i=1,lmax
	  x(i) = thet(i)
	  y(i) = yexp(i)/ynorm
	  er(i) = yerr(i)/ynorm
28	continue
	kind1 = -1
c	write (3,*) 'before 1st line'
	call line (x, y, er, lmax, xmin, xmax, YMIN, YMAX, kind1, lin)
c	write (3,*) 'after 1st line'
*	do 30 k=numset,numset
31	do 29 i=1,npts
	  x(i) = i - 1
	  er(i) = 0
29	continue
*	a(1) = 1
	call legendre ( x, y, a, npts)
*	call legnorm (a(3), a(5), ynorm)
*	  do i=1,npts
*	  y(i) = ynorm * y(i)
*	  end do
c	write (3,*) 'before 2nd line'
	call line (x, y, er, npts, xmin, xmax, YMIN, YMAX, kind, lin)
c	write (3,*) 'after 2nd line'
*30	continue

	write (6,*) '     ',deltamin(k), a(3),a(5)


	call movabs ( 0, 0 )
50	call scursr ( ic, ix, iy )
	call movabs ( ix, 0 )

	if ( ic .ge. 97 ) ic = ic - 32		! Uppercase = Lowercase.
	if ( ic .eq. pkey ) then
	  call hdcopy
	else if ( ic .eq. spkey ) then
	  call movabs ( 0, 750 )
	  call anmode
	  write ( 5,1187 ) AJ1(k), AJ2(k), deltamin(k), a(3), a(5)
1187      format(' Ji = ', f4.1,' Jf = ', f4.1,'  Delta = ',F5.1,
	1	4X,'A2 = ',F7.3,4X,'A4 = ',F7.3)
	else if ( ic .eq. hkey ) then
	  call anmode
	  if (jterm .eq. 0) call vtmode
	  if (jterm .eq. 1) call onlyal
	  write (6,488)
488	  format ('     Menu					',/,
     +		   '   ------					',/,
     +	  ' d: input delta					',/,
     +	  ' h: help						',/,
     +	  ' l: legendre polynomial fit				',/,
     +	  ' n: new screen					',/,
     +	  ' o: option: enter a2, a4				',/,
     +	  ' p: print hardcopy					',/,
     +	  ' s: stop						',/,
     +	  ' w: write out data',/,
     +    ' x: exit						',/,
     +	  ' To continue type any number				',/)
	  read (5,*)  junk
	  goto 300
C________________________________________________
CCC This section is added by Tai.
	else if ( ic .eq. wkey ) then 

C     for data points
      OPEN ( 25, FILE = 'plot_exp.dat', form = 'formatted', STATUS = 'unknown')
	  do i=1,lmax
	   write(25,*) thet(i), yexp(i)/ynorm, yerr(i)/ynorm
	  end do
	  close(25)

C	  for curve
	  OPEN ( 25, FILE = 'plot_theo.dat', form = 'formatted', STATUS = 'unknown')
	  do i=1,npts
	   write(25,*) i, y(i)
	  end do
	  close(25)
	  goto 300	
C________________________________________________
	else if ( ic .eq. dkey ) then		! Use d key to input new Delta.
	  call movabs (0, 750)
	  call anmode
	  write (6,515) 
 515	  format (' Input new Delta ')
	  read (5,*) deltamin(k)
	  goto 100
	else if ( ic .eq. nkey ) then
	  goto 300
	else if ( ic .eq. okey ) then
	  call movabs (0, 730)
	  call anmode
	  write (6,*) ' Enter new A2, A4: '
	  read (5,*) a(3), a(5)
	  kind = 1
	  goto 31
	else if ( ic .eq. lkey ) then
	  call anmode
	  if (jterm .eq. 0) call vtmode
	  if (jterm .eq. 1) call onlyal
	  do i=1, lmax
	    angle(i) = thet(i)
	    yield(i) = yexp(i)
	    sigmay(i) = yerr(i)
	  end do
	  norder = 4				! fit up to P(4).
	  neven = 1				! fit only even P's.
	  modus = -1				! statistical weights.
	  call legfitc ( angle, yield, sigmay, lmax, norder, neven, 
     +		modus, ftest, yfit, a, sigmaa, b, sigmab, chisqr )
c	  a(1) = 1.
	  a(2) = 0.
	  a(4) = 0.
	  a(3) = b(3)
	  a(5) = b(5)
	  write (6,*) '  Fit Results:'
	  write (6,*) ' --------------'
	  write (6,700) a(1), sigmab(1)
	  write (6,710) a(3), sigmab(3)
	  write (6,720) a(5), sigmab(5)
	  write (6,*) ' Chisqr = ', chisqr
700	  format (' A0 = ', f6.3,' +/-', f6.3 ) 
710	  format (' A2 = ', f6.3,' +/-', f6.3 ) 
720	  format (' A4 = ', f6.3,' +/-', f6.3 ) 
	  read (5,*)  inum
	  if (inum .eq. 0) return
	  kind = 1
	  goto 300
	else if ( ic .eq. skey ) then
	  if (jterm .eq. 0) call vtmode
	  if (jterm .eq. 1) call onlyal
	  return				! return to program AD.
	else if ( ic .eq. xkey ) then
	  if (jterm .eq. 0) call vtmode
	  if (jterm .eq. 1) call onlyal
	  return				! return to program AD.
	else
	  goto 50
	end if

	goto 50

	end



