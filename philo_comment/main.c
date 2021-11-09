#include "./philo.h"

void	*ph_life(void *ph_info)
{
	t_ph	*ph;

	ph = (t_ph *)ph_info;
	ph->last_eat = present(ph);
	if (ph->id % 2 == 0) //교착상태에 뻐자자 않게 비대칭성 부여
		usleep(42);
	while (42)
	{
		if (ph_eat(ph))
			break ;
		if (ph_sleep(ph))
			break ;
		if (ph_think(ph))
			break ;
	}
	return (NULL);
}

int	birth_philo(t_ph *ph, t_info **info)
{
	int		idx;
	int		check;

	idx = -1;
	check = 0;
	while (++idx < (*info)->ph_num)
	{
		ph[idx].in = *info; //in에 기본적인 정보들 담아둠
		ph[idx].id = idx + 1; // philo number
		ph[idx].eat = 0; //먹는 횟수
		ph[idx].die = 0; //philo가 죽었는지 확인하는 flag
		check = pthread_create(&ph[idx].thrd, 0, ph_life, &ph[idx]); //philo당 하나의 thread 생성
		if (check != 0)
		{
			free(*info);
			free(ph);
			return (print_error());
		}
		pthread_detach(ph[idx].thrd);
	}
	return (0);
}

int	info_parsing(t_info **info)
{
	int		check;
	int		idx;

	idx = -1;
	while (++idx < (*info)->ph_num)
	{
		check = pthread_mutex_init(&(*info)->fork[idx], NULL); //mutex 객체 초기화
		if (check != 0)
			return (print_error());
	}
	gettimeofday(&(*info)->st, NULL); //시간 구하는 함수
	(*info)->st_t = (*info)->st.tv_sec * 1000 + (*info)->st.tv_usec / 1000; //?
	return (0);
}

int	main(int argc, char **argv)
{
	int			idx;
	int			check;
	t_info		*info;
	t_ph		*ph;

	if (argc != 5 && argc != 6)
		return (print_error());
	check = ph_init(argc, argv, &info, &ph);
	if (check == -1)
		return (print_error());
	if (info_parsing(&info))
		return (-1);
	if (birth_philo(ph, &info))
		return (-1);
	idx = -1;
	while (1)
	{
		if (ph[++idx].die == 1 || check_eatcount(ph))
			break ;
		if (idx == info->ph_num - 1)
			idx = -1;
	}
	return (0);
}
