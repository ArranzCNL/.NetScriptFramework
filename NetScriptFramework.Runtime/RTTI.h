#pragma once

#pragma pack (push, rttidata, 4)
struct crtti__PMD
{
	int mdisp;
	int pdisp;
	int vdisp;
};

const struct crtti__RTTIBaseClassDescriptor
{
	unsigned int pTypeDescriptor;
	int numContainedBases;
	crtti__PMD where;
	int attributes;
};

#pragma warning (disable:4200)
const struct crtti__RTTIBaseClassArray
{
	int arrayOfBaseClassDescriptors[];
};
#pragma warning (default:4200)

const struct crtti__RTTIClassHierarchyDescriptor
{
	int signature;
	int attributes;
	int numBaseClasses;
	int pBaseClassArray;
};

const struct crtti__RTTICompleteObjectLocator
{
	int signature;
	int offset;
	int cdOffset;
	unsigned int pTypeDescriptor;
	int pClassDescriptor;
	int pBaseObject;
};

/*
_obj = actual pointer of object where *_obj is vtable
_target = RTTI target value WITHOUT the base module address
_module = base address of module we are looking in
*/
void * crtti__RTDynamicCast(void * _obj, unsigned int _target, void * _module)
{
	Pointer module = (Pointer)_module;
	Pointer obj = (Pointer)_obj;

	void * result = NULL;

	__try
	{
		Pointer vtable = *((Pointer*)obj);
		crtti__RTTICompleteObjectLocator * loc = *((crtti__RTTICompleteObjectLocator**)(vtable - sizeof(Pointer)));
		do
		{
			if (loc->offset != 0)
			{
				obj -= loc->offset;
				vtable = *((Pointer*)obj);
				loc = *((crtti__RTTICompleteObjectLocator**)(vtable - sizeof(Pointer)));
				continue;
			}

			break;
		} while (true);

		if (loc->pTypeDescriptor == _target)
			result = (void*)obj;
		else if(loc->pClassDescriptor != 0)
		{
			crtti__RTTIClassHierarchyDescriptor * hierarchy = (crtti__RTTIClassHierarchyDescriptor*)(module + loc->pClassDescriptor);
			if (hierarchy->pBaseClassArray != 0)
			{
				crtti__RTTIBaseClassArray * arr = (crtti__RTTIBaseClassArray*)(module + hierarchy->pBaseClassArray);
				for (int i = 0; i < hierarchy->numBaseClasses; i++)
				{
					crtti__RTTIBaseClassDescriptor * base = (crtti__RTTIBaseClassDescriptor*)(module + arr->arrayOfBaseClassDescriptors[i]);
					if (base->pTypeDescriptor == _target)
					{
						obj += base->where.mdisp;
						result = (void*)obj;
						break;
					}
				}
			}
		}
	}
	__except (1)
	{

	}

	return result;
}

void crtti__Explore(void* _obj, Pointer* baseObj, Pointer* data, int maxDataCount, void* _module)
{
	Pointer module = (Pointer)_module;
	Pointer obj = (Pointer)_obj;

	__try
	{
		Pointer vtable = *((Pointer*)obj);
		crtti__RTTICompleteObjectLocator * loc = *((crtti__RTTICompleteObjectLocator**)(vtable - sizeof(Pointer)));
		do
		{
			if (loc->offset != 0)
			{
				obj -= loc->offset;
				vtable = *((Pointer*)obj);
				loc = *((crtti__RTTICompleteObjectLocator**)(vtable - sizeof(Pointer)));
				continue;
			}

			break;
		} while (true);

		*baseObj = obj;

		if (loc->pClassDescriptor != 0)
		{
			int szEntry = 2;

			crtti__RTTIClassHierarchyDescriptor * hierarchy = (crtti__RTTIClassHierarchyDescriptor*)(module + loc->pClassDescriptor);
			if (hierarchy->pBaseClassArray != 0)
			{
				crtti__RTTIBaseClassArray * arr = (crtti__RTTIBaseClassArray*)(module + hierarchy->pBaseClassArray);
				for (int i = 0; i < hierarchy->numBaseClasses; i++)
				{
					crtti__RTTIBaseClassDescriptor * base = (crtti__RTTIBaseClassDescriptor*)(module + arr->arrayOfBaseClassDescriptors[i]);
					if ((i + 1) * szEntry > maxDataCount)
					{
						*baseObj = 0;
						break;
					}

					data[i * szEntry] = base->pTypeDescriptor;
					data[i * szEntry + 1] = base->where.mdisp;
				}
			}
		}
	}
	__except (1)
	{
		*baseObj = 0;
	}
}

#pragma pack (pop, rttidata)
