function particle_step(i,particle, delta)

	particle.time = particle.time - delta
	
	if (particle.time < 0) then
		bf:remove_flat_block(particle.block)
		table.remove(particles,i)
	else
	
		particle.block:move(Vector3f((particle.motion.x-particle.scale/2)*delta,particle.motion.y*delta,(particle.motion.z-particle.scale/2)*delta))
		
		particle.block:rotate(Vector3f(particle.rotation.x*delta,particle.rotation.y*delta,particle.rotation.z*delta))
		
		particle.block:change_size(1+delta*particle.scale)
	
	end
end


function new_particle(image,size,scale,position,motion,rotation,life)

	particle = {}
	particle.block = bf:new_flat_block(image,size,true)
	particle.block:move(position)
	particle.block:rotate(Vector3f(-90,0,0))
	--particle.block:set_rel_centre(true)
	particle.scale = scale
	particle.motion = motion
	particle.rotation = rotation
	particle.time = life

	table.insert(particles,particle)

end

function new_smoke(position)

	new_particle("cloud.bmp",Vector2f(5,5),0.3,position,Vector3f(0,2,0),Vector3f(0,0,0),1)
	--new_particle("cloud.bmp",Vector2f(1,1),1.2,position,Vector3f(0,0.2,0),Vector3f(0,0.2,0),10)
end
